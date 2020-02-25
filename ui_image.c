
#include "mcc_generated_files/sd_spi/sd_spi.h"
#include "mcc_generated_files/fatfs/ff.h"

#include "ui.h"

#include "lcd_ILI9341.h"

FATFS drive;

bool SD_OpenDrive(FATFS* drive) {
    if (SD_SPI_IsMediaPresent() == false) {
        return false;
    }

    if (f_mount(drive, "0:", 1) == FR_OK) {
        return true;
    }
    return false;
}

static bool SD_DriveInit() {
    return SD_OpenDrive(&drive);
}

//static bool SD_CloseDrive() {
//    if (!f_mount(0, "0:", 0)) {
//        return false;
//    }
//    return true;
//}

void UI_ImageInit() {
    SD_DriveInit();
}

void UI_DrawImage() {
    FIL file;
    if (f_open(&file, "LOGO.BMP", FA_READ) != FR_OK) {
        return;
    }
    LCD_WriteBitmapFile(&file, 0, (ILI9341_TFTHEIGHT - 185) / 2);
    f_close(&file);
}
