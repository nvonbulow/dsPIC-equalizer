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
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/dma.h"

#include "lcd_ILI9341.h"
#include "mcc_generated_files/ptg.h"

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

// PTG Timer Limit = Fosc/2 * t = Fosc/2 * 1/f

uint16_t adc_values[1024];

/*
                         Main application
 */
int main(void) {
    bool bmp_written = false;
    FATFS drive;
    FIL file;
    UINT result;
    int conversion, i;
    
    // initialize the device
    SYSTEM_Initialize();
    
    IO_LED_SetHigh();
    // Set up DMA such that data is automagically copied into the buffer
    DMA_SourceAddressSet(DMA_CHANNEL_0, (uint16_t) &ADCBUF0);
    DMA_DestinationAddressSet(DMA_CHANNEL_0, (uint16_t) adc_values);
    DMA_TransferCountSet(DMA_CHANNEL_0, 1024);
    DMA_ChannelEnable(DMA_CHANNEL_0);
    PTG_Enable();
    PTG_StartStepSequence();
    
    LCD_Begin();
    
    while (1) {
        
        LCD_FillScreen(ILI9341_DARKGREEN);
        DELAY_milliseconds(500);
        LCD_FillScreen(ILI9341_MAROON);
        DELAY_milliseconds(500);
    }
    return 1; 
}

void PTG_Trigger0_CallBack(void) {
    IO_LED_SetLow();
}
/**
 End of File
*/

