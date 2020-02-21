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

#include "dac.h"
#include "lcd_ILI9341.h"
#include "stream.h"

/*
    Main application
 */
int main(void) {
    uint16_t i = 0;
    // initialize the device
    SYSTEM_Initialize();
    STREAM_Initialize();
    
    IO_LED_SetHigh();
    
    LCD_Begin();
    
    STREAM_InputEnable();
    
    for(i = 0; i < 1024; i++) {
        uint16_t val = DAC_VoltageToValue(2048-i*2);
        STREAM_output_buffers[0][i] = val;
    }
    
    STREAM_OutputEnable();
    
    while (1) {
//        uint16_t *input_buffer, *output_buffer;
//        while(!STREAM_InputBufferReady());
//        input_buffer = STREAM_GetWorkingInputBuffer();
//        output_buffer = STREAM_GetWorkingOutputBuffer();
//        
//        memcpy((void*) output_buffer, (void*) input_buffer, STREAM_BUFFER_SIZE * sizeof(uint16_t));
    }
    return 1; 
}
/**
 End of File
*/

