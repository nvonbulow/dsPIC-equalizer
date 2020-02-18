#include "lcd_ILI9341.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/drivers/spi_master.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/fatfs/ff.h"


#define LCD_SPI_ChipSelect() LCD_CS_SetLow()
#define LCD_SPI_ChipDeselect() LCD_CS_SetHigh()
#define LCD_SPI_DC_CmdMode() LCD_DC_SetLow()
#define LCD_SPI_DC_DataMode() LCD_DC_SetHigh()
#define LCD_SPI_WriteByte(data) spiMaster[LCD].writeByte(data)
#define LCD_SPI_WriteBlock(data, length) spiMaster[LCD].writeBlock(data, length)
#define LCD_SPI_ExchangeByte(data) spiMaster[LCD].exchangeByte(data)
#define LCD_SPI_ExchangeBlock(data, length) spiMaster[LCD].exchangeBlock(data, length)
#define LCD_SPI_MasterOpen() spiMaster[LCD].spiOpen()
#define LCD_SPI_Close() spiMaster[LCD].spiClose()

#define LCD_SPI_Start() if(LCD_SPI_Start_() == false) { return false; }
#define LCD_SPI_End() LCD_SPI_End_()

#define LCD_WIDTH ILI9341_TFTWIDTH
#define LCD_HEIGHT ILI9341_TFTHEIGHT

#define LCD_SPI_CLKSPEED 40000000
// Delays 2 SPI clock periods
// Only really applies if SPI_CLKSPEED < 1000000, otherwise delay is zero
#define LCD_SPI_Delay() DELAY_microseconds(2000/LCD_SPI_CLKSPEED);

// The sequence of commands needed to initialize the display
// Taken from the Adafruit library
static const uint8_t initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
  ILI9341_PIXFMT  , 1, 0x55,
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_SLPOUT  , 0x80,                // Exit Sleep
  ILI9341_DISPON  , 0x80,                // Display on
  0x00                                   // End of list
};

// Low level byte sending
bool LCD_sendCommand(uint8_t, const uint8_t*, uint8_t);
void LCD_writeCommand(uint8_t);
bool LCD_writeByte(uint8_t);
bool LCD_writeWord(uint16_t);

// High level private functions
void LCD_setAddressWindow(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height);

inline bool LCD_SPI_Start_() {
    if(LCD_SPI_MasterOpen() == false) {
        return false;
    }
    LCD_SPI_ChipSelect();
    return true;
}

inline void LCD_SPI_End_() {
    LCD_SPI_Delay(); // Allow the last byte to finish sending
    LCD_SPI_ChipDeselect();
    LCD_SPI_Close();
}

inline void LCD_SPI_CmdMode() {
    LCD_SPI_DC_CmdMode();
    LCD_SPI_Delay();
}

inline void LCD_SPI_DataMode() {
    LCD_SPI_DC_DataMode();
    LCD_SPI_Delay();
}

void LCD_Begin() {
    uint8_t cmd, x, numArgs;
    const uint8_t *addr = initcmd;
    // Send software reset
    LCD_writeCommand(ILI9341_SWRESET);
    LCD_writeCommand(ILI9341_SWRESET);
    DELAY_milliseconds(150);
    
    while((cmd = *(addr++)) > 0) {
        x = *(addr++);
        numArgs = x & 0x7F; // MSB indicates a delay of 150ms, so ignore this
        LCD_sendCommand(cmd, addr, numArgs);
        addr += numArgs;
        // Some commands require a delay, indicated by the MSB of numArgs
        if(x & 0x80) {
            DELAY_milliseconds(150);
        }
    }
    
    LCD_FillScreen(ILI9341_BLACK);
}

// Write a command with data arguments and leave in data mode
bool LCD_sendCommand(uint8_t commandByte, const uint8_t *dataBytes, uint8_t numDataBytes) {
    // Begin SPI transaction
    LCD_SPI_Start();
    // Send the command
    LCD_SPI_CmdMode();
    LCD_SPI_ExchangeByte(commandByte);
    LCD_SPI_Delay(); // Allow byte to finish sending
    // Send the associated data
    LCD_SPI_DataMode();
    if(dataBytes) {
        LCD_SPI_WriteBlock((void*) dataBytes, numDataBytes);
    }
    
    LCD_SPI_End();
    
    return true;
}

bool LCD_writeByte(uint8_t data) {
    LCD_SPI_Start();
    
    LCD_SPI_ExchangeByte(data);
    
    LCD_SPI_End();
    
    return true;
}

bool LCD_writeWord(uint16_t data) {
    uint8_t order[2] = {data >> 8, data};
    LCD_SPI_Start();
    
    LCD_SPI_WriteBlock(order, 2);
    
    LCD_SPI_End();
    
    return true;
}

bool LCD_writeReverseWord(uint16_t data) {
    uint8_t order[2] = {data, data >> 8};
    LCD_SPI_Start();
    
    LCD_SPI_WriteBlock(order, 2);
    
    LCD_SPI_End();
    
    return true;
}

void LCD_writeCommand(uint8_t commandByte) {
    LCD_SPI_CmdMode();
    LCD_writeByte(commandByte);
    LCD_SPI_DataMode();
}

void LCD_setAddressWindow(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height) {
    uint16_t x2 = (x1 + width -1), y2 = (y1 + height - 1);
    LCD_writeCommand(ILI9341_CASET); // Column address set
    LCD_writeWord(x1);
    LCD_writeWord(x2);
    LCD_writeCommand(ILI9341_PASET); // Row address set
    LCD_writeWord(y1);
    LCD_writeWord(y2);
    LCD_writeCommand(ILI9341_RAMWR); // Write to ram
}

void LCD_writeColor(uint16_t color, uint32_t count) {
    while(count-- > 0) {
        LCD_writeWord(color);
    }
}

void LCD_WritePixel(uint16_t x, uint16_t y, uint16_t color) {
    if(x >= 0 && x < LCD_WIDTH && y >= 0 && y < LCD_HEIGHT) {
        LCD_setAddressWindow(x, y, 1, 1);
        LCD_writeWord(color);
    }
    
    // End RAM Write
    LCD_writeCommand(ILI9341_NOP);
}

void LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    uint32_t i, num_pixels = (uint32_t) width * height;
    LCD_setAddressWindow(x, y, width, height);
    
    for(i = 0; i < num_pixels; i++) {
        LCD_writeWord(color);
    }
    
    // End RAM Write
    LCD_writeCommand(ILI9341_NOP);
}

void LCD_WriteBitmap(uint16_t* pixels, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    uint32_t i, num_pixels = (uint32_t) width * height;
    LCD_setAddressWindow(x, y, width, height);
    
    for(i = 0; i < num_pixels; i++) {
        LCD_writeWord(pixels[i]);
    }
    
    // End RAM Write
    LCD_writeCommand(ILI9341_NOP);
}

bool LCD_WriteBitmapFile(FIL* file, uint16_t x, uint16_t y) {
    FRESULT result;
    UINT bytes_read;
    uint32_t start_addr, width, height, i;
    int32_t row, col;
    uint16_t pixel_buf[512];
    // 0x0A contains the starting address of pixel data
    // 4 bytes
    result = f_lseek(file, 0x0A);
    result = f_read(file, &start_addr, sizeof(start_addr), &bytes_read);
    
    // 0x12 and 0x16 respectively are the width and height of the bitmap
    // Each are 4 bytes, so a uint32 is needed
    result = f_lseek(file, 0x12);
    result = f_read(file, &width, sizeof(width), &bytes_read);
    result = f_read(file, &height, sizeof(height), &bytes_read);
    
    // bytes_left = (int32_t) width * height * 2;
    
    result = f_lseek(file, start_addr);
    
    row = height;
    col = 0;
    // bitmap files are bottom-up, so we need to render the bottom line first
    while(row >= 0 && bytes_read > 0) {
        // Read a row of pixels
        result = f_read(file, pixel_buf, width * sizeof(uint16_t), &bytes_read);
        
        // And render them if the row is on the screen
        if(row >= LCD_HEIGHT) {
            continue;
        }
        LCD_setAddressWindow(x, y + row, x + width, 1);
        // x + i < LCD_WIDTH ensures that clipping occurs correctly
        for(i = 0; x + i < LCD_WIDTH && i < bytes_read / 2; i++) {
            LCD_writeWord(pixel_buf[i]);
        }
        // End RAM Write
        LCD_writeCommand(ILI9341_NOP);
        
        row--;
    }
    
    return true;
}

void LCD_WriteBitmapScaled(uint16_t* pixels, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t scaling) {
    uint32_t row, col, row_scaled, col_scaled;
    LCD_setAddressWindow(x, y, width * scaling, height * scaling);
    
    for(row = 0; row < height; row++) {
        // Write each row scaling times
        for(row_scaled = 0; row_scaled < scaling; row_scaled++) {
            for(col = 0; col < width; col++) {
                // Write each colum scaling times
                for(col_scaled = 0; col_scaled < scaling; col_scaled++) {
                    LCD_writeWord(pixels[row*width + col]);
                }
            }
        }
    }
    // End RAM Write
    LCD_writeCommand(ILI9341_NOP);
}

void LCD_Invert(bool invert) {
    LCD_writeCommand(invert? ILI9341_INVON : ILI9341_INVOFF);
}