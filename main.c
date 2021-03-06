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
#include <math.h>
#include <string.h> // memcpy

#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/fatfs/ff.h"
#include "mcc_generated_files/sd_spi/sd_spi.h"

#include "dac.h"
#include "equalizer.h"
#include "lcd_ILI9341.h"
#include "stream.h"
#include "ui.h"

#include <dsp.h>

// FIR Filter related stuff
// Open filter.fda in MATLAB to see the filter
#include "fdacoefs_bands.h"
#include "equalizer_presets.h"

uint16_t BUTTONCOUNT = 0;

enum {
    AUDIO,
    IMAGE
} mode = AUDIO;

/*
    Main application
 */
int main(void) {
    bool sel_btn_pressed = false;
    bool mode_btn_pressed = false;

    // initialize the device
    SYSTEM_Initialize();
    STREAM_Initialize();
    
    LCD_Begin();
    
    UI_AudioInit();
    UI_ImageInit();
    
    STREAM_InputEnable();
    STREAM_OutputEnable();
    
    EQUALIZER_Initialize();
    EQUALIZER_SetEqPreset(BUTTONCOUNT);
    
    UI_DrawBarChart((fractional*) eq_presets[BUTTONCOUNT], ILI9341_GREEN);
    
    while (1) {
        uint16_t *input_buffer, *output_buffer;
        
        // Check if button was pressed to switch filters
        if(sel_btn_pressed && IO_SEL_GetValue()) {
            // button was released so toggle the filter
            BUTTONCOUNT = (BUTTONCOUNT + 1) % NUMFILTERS;
        }
        sel_btn_pressed = !IO_SEL_GetValue();
        
        // Check if button was pressed to switch between mode
        if(mode_btn_pressed && IO_MODE_GetValue()) {
            // button was released so toggle the filter
            mode = (mode + 1) % 2;
            // Also clear the screen
            LCD_FillScreen(ILI9341_BLACK);
            
            // Draw the image if in image mode now
            if(mode == IMAGE) {
                UI_DrawImage();
            }
            else if(mode == AUDIO) {
                UI_AudioInit();
            }
        }
        mode_btn_pressed = !IO_MODE_GetValue();
        
        EQUALIZER_SetEqPreset(BUTTONCOUNT);
        
        if(mode == AUDIO) {
            UI_DrawBarChart(eq_presets[BUTTONCOUNT], ILI9341_GREEN);
            IO_LED_SetHigh();
        }
        else if(mode == IMAGE) {
            IO_LED_SetLow();
        }
        
        // Wait for buffer to fill up
        while(!STREAM_InputBufferReady());
        input_buffer = STREAM_GetWorkingInputBuffer();
        output_buffer = STREAM_GetWorkingOutputBuffer();
        
        EQUALIZER_Apply(output_buffer, input_buffer);
    }
    return 1; 
}

/**
 End of File
*/

