/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  dsPIC33CK256MP202
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.41
        MPLAB 	          :  MPLAB X v5.30
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/fatfs/ff.h"
#include "mcc_generated_files/sd_spi/sd_spi.h"

#include "lcd_ILI9341.h"

// #include "images/rose_logo.h"

bool SD_OpenDrive(FATFS* drive) {
    if( SD_SPI_IsMediaPresent() == false) {
        return false;
    }

    if (f_mount(drive, "0:", 1) == FR_OK) {
        return true;
    }
    return false;
}

bool SD_CloseDrive() {
    if(!f_mount(0,"0:",0)) {
        return false;
    }
    return true;
}

/*
                         Main application
 */
int main(void) {
    bool bmp_written = false;
    FATFS drive;
    FIL file;
    UINT result;
    // initialize the device
    SYSTEM_Initialize();
    if(!SD_OpenDrive(&drive)) {
        IO_LED_SetHigh();
        while(1);
    }
    LCD_Begin();
    DELAY_milliseconds(5);
    
    // Add your application code
    while (1) {
        
        if(IO_PB_GetValue() == 0) {
            if(bmp_written) {
                LCD_FillScreen(ILI9341_BLACK);
                DELAY_milliseconds(50);
                bmp_written = false;
            }
            else {
                //LCD_WriteBitmapScaled((uint16_t*)rose_logo_img, 0, 0, 100, 150, 2);
                if((result = f_open(&file, "LOGO.BMP", FA_READ)) != FR_OK) {
                    IO_LED_SetHigh();
                    continue;
                }
                IO_LED_SetLow();
                LCD_WriteBitmapFile(&file, 0, (320-185)/2);
                f_close(&file);
                DELAY_milliseconds(50);
                bmp_written = true;
            }
        }
        
    }
    return 1; 
}
/**
 End of File
*/

