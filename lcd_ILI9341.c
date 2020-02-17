#include "lcd_ILI9341.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/drivers/spi_master.h"
#include "mcc_generated_files/delay.h"


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

#define LCD_SPI_Delay() DELAY_milliseconds(1);

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

bool LCD_sendCommand(uint8_t, const uint8_t*, uint8_t);
void LCD_writeCommand(uint8_t);
bool LCD_writeByte(uint8_t);
bool LCD_writeWord(uint16_t);

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
    
    while((cmd = *(addr++)) > 0) {
        x = *(addr++);
        numArgs = x & 0x7F;
        LCD_sendCommand(cmd, addr, numArgs);
        addr += numArgs;
        // Some commands require a delay
        if(x & 0x80) {
            DELAY_milliseconds(150);
        }
    }
}

// Write a command with data arguments and leave in data mode
bool LCD_sendCommand(uint8_t commandByte, const uint8_t *dataBytes, uint8_t numDataBytes) {
    // Begin SPI transaction
    LCD_SPI_Start();
    // Send the command
    LCD_SPI_CmdMode();
    LCD_SPI_WriteByte(commandByte);
    
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
    
    LCD_SPI_WriteByte(data);
    
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

void LCD_writeCommand(uint8_t commandByte) {
    LCD_SPI_CmdMode();
    LCD_writeByte(commandByte);
    LCD_SPI_DataMode();
}

void LCD_setAddress(uint16_t x1, uint16_t y1, uint16_t width, uint16_t height) {
    uint16_t x2 = (x1 + width -1), y2 = (y1 + height - 1);
    LCD_writeCommand(ILI9341_CASET); // Column address set
    LCD_writeWord(x1);
    LCD_writeWord(x2);
    LCD_writeCommand(ILI9341_PASET); // Row address set
    LCD_writeWord(y1);
    LCD_writeWord(y2);
    LCD_writeCommand(ILI9341_RAMWR); // Write to ram
}

void LCD_WritePixel(uint16_t x, uint16_t y, uint16_t color) {
    if(x >= 0 && x < LCD_WIDTH && y >= 0 && y < LCD_HEIGHT) {
        LCD_setAddress(x, y, 1, 1);
        LCD_writeWord(color);
    }
}

void LCD_Invert(bool invert) {
    LCD_writeCommand(invert? ILI9341_INVON : ILI9341_INVOFF);
}