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

#include <dsp.h>

inline fractional U12_Q15(uint16_t val) {
    // Data is in the range 0..4096, which is 12 bits
    // We want it in the range -0.5..0.5
    // We'll normalize the data so it's in the range 0..1 by shifting left
    // 3 bits (fractional is bits 0..14), and then subtract 0.5 to get it in
    // the -0.5..0.5 range
    return (val << 3) - Q15(0.5f);
}

inline uint16_t Q15_U12(fractional val) {
    // Just reverse the operations
    return (val + Q15(0.5f)) >> 3;
}

// The coefficients of the FIR filter. These can range from [-1..1)
fractional filter_coeffs[1]
    __attribute__((space (xmemory)))
     = { Q15(0.99f) };

// FIR input buffer
fractional filter_in[STREAM_BUFFER_SIZE];

// FIR output buffer
fractional filter_out[STREAM_BUFFER_SIZE];

// FIR delay buffer
fractional filter_delay[STREAM_BUFFER_SIZE]
    __attribute__((space (ymemory)));

FIRStruct filter;

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
    
//    for(i = 0; i < 1024; i++) {
//        uint16_t val = DAC_VoltageToValue(2048-i*2);
//        STREAM_output_buffers[0][i] = val;
//    }
    
    STREAM_OutputEnable();
    
    // FIR filter setup
    FIRStructInit(&filter, 1, filter_coeffs, COEFFS_IN_DATA, filter_delay);
    
    while (1) {
        uint16_t *input_buffer, *output_buffer;
        
        // Wait for buffer to fill up
        while(!STREAM_InputBufferReady());
        input_buffer = STREAM_GetWorkingInputBuffer();
        output_buffer = STREAM_GetWorkingOutputBuffer();
        
        // convert input data to Q15 format
        for(i = 0; i < STREAM_BUFFER_SIZE; i++) {
            filter_in[i] = U12_Q15(input_buffer[i]);
        }
        
        // Run the filter
        FIR(STREAM_BUFFER_SIZE, filter_out, filter_in, &filter);
        
        // convert output data to U12 format
        for(i = 0; i < STREAM_BUFFER_SIZE; i++) {
            output_buffer[i] = Q15_U12(output_buffer[i]);
        }
        
        // memcpy((void*) output_buffer, (void*) input_buffer, STREAM_BUFFER_SIZE * sizeof(uint16_t));
    }
    return 1; 
}
/**
 End of File
*/

