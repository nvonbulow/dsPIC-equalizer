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

// FIR Filter related stuff
// Open filter.fda in MATLAB to see the filter
#include "fdacoefs_bands.h"
#include "equalizer_presets.h"

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
fractional filter_coeffs[NUM_COEFFS]
    __attribute__((space (xmemory)));

// FIR input buffer
fractional filter_in[STREAM_BUFFER_SIZE];

// FIR output buffer
fractional filter_out[STREAM_BUFFER_SIZE];

// FIR delay buffer
fractional filter_delay[STREAM_BUFFER_SIZE]
    __attribute__((space (ymemory)));

FIRStruct filter;

bool filter_enabled = false;

// FFT related stuff
fractcomplex twiddle_factors[STREAM_BUFFER_SIZE/2]
    __attribute((space (xmemory), aligned(STREAM_BUFFER_SIZE * sizeof(fractcomplex) / 2)));

fractcomplex fft_in[STREAM_BUFFER_SIZE]
    __attribute__((space (ymemory), aligned (STREAM_BUFFER_SIZE * sizeof(fractcomplex))));

fractcomplex fft_out[STREAM_BUFFER_SIZE]
    __attribute__((space (ymemory), aligned (STREAM_BUFFER_SIZE * sizeof(fractcomplex))));

fractional coeff_buffer[NUM_COEFFS];

uint16_t BUTTONCOUNT = 0;

void CoeffBandGain(fractional* dst, fractional** bands, fractional* gains, uint16_t num_bands) {
    int i;
    // Initialize dst with 0
    memset(dst, 0, sizeof(fractional) * NUM_COEFFS);
    for(i = 0; i < num_bands; i++) {
        // Copy to temp buffer
        memcpy(coeff_buffer, bands[i], sizeof(fractional) * NUM_COEFFS);
        VectorScale(NUM_COEFFS, coeff_buffer, coeff_buffer, gains[i]);
        VectorAdd(NUM_COEFFS, dst, dst, coeff_buffer);
    }
    // We done here bruh
}

/*
    Main application
 */
int main(void) {
    uint16_t i = 0;
    bool button_pressed = false;
    // initialize the device
    SYSTEM_Initialize();
    STREAM_Initialize();
    
    // Calculate Twiddle factors for FFT
    // N is log2(STREAM_BUFFER_SIZE)
    TwidFactorInit(9, twiddle_factors, 0);
    
    LCD_Begin();
    
    barChartInit();
    
    STREAM_InputEnable();
    
//    for(i = 0; i < 1024; i++) {
//        uint16_t val = DAC_VoltageToValue(2048-i*2);
//        STREAM_output_buffers[0][i] = val;
//    }
    
    STREAM_OutputEnable();
    
    CoeffBandGain(filter_coeffs, BANDS, eq_presets[BUTTONCOUNT], 7);
    
    drawBarChart(eq_presets[BUTTONCOUNT], ILI9341_GREEN);
            
    // FIR filter setup
    // Uses coefficents defined in main.c
    // FIRStructInit(&filter, sizeof(filter_coeffs) / sizeof(fractional), filter_coeffs, COEFFS_IN_DATA, filter_delay);
    // Uses coefficients in fdacoefs.h (generated by MATLAB)
    FIRStructInit(&filter, NUM_COEFFS, filter_coeffs, COEFFS_IN_DATA, filter_delay);
    FIRDelayInit(&filter);
    
    while (1) {
        uint16_t *input_buffer, *output_buffer;
        
        // Check if button was pressed to either enable or disable the filter
        if(button_pressed && IO_BTN_GetValue()) {
            // button was released so toggle the filter
//            filter_enabled = !filter_enabled;
            BUTTONCOUNT++;
            if (BUTTONCOUNT == 10){
                BUTTONCOUNT = 0;
            }
        }
            
        button_pressed = !IO_BTN_GetValue();
        
        IO_LED_SetHigh();
        CoeffBandGain(filter_coeffs, BANDS, eq_presets[BUTTONCOUNT], 7);
        drawBarChart(eq_presets[BUTTONCOUNT], ILI9341_GREEN);
        
        
        // Wait for buffer to fill up
        while(!STREAM_InputBufferReady());
        input_buffer = STREAM_GetWorkingInputBuffer();
        output_buffer = STREAM_GetWorkingOutputBuffer();
        
        // convert input data to Q15 format
        for(i = 0; i < STREAM_BUFFER_SIZE; i++) {
            filter_in[i] = U12_Q15(input_buffer[i]);
            fft_in[i].real = filter_in[i];
        }
        
        FIR(STREAM_BUFFER_SIZE, filter_out, filter_in, &filter);
        
        FFTComplex(9, fft_out, fft_in, twiddle_factors, COEFFS_IN_DATA);
        
        // convert output data to U12 format
        for(i = 0; i < STREAM_BUFFER_SIZE; i++) {
            output_buffer[i] = Q15_U12(filter_out[i]);
        }
        
        // memcpy((void*) output_buffer, (void*) input_buffer, STREAM_BUFFER_SIZE * sizeof(uint16_t));
    }
    return 1; 
}

#define NUMBARS 7
#define GAPWIDTH 5
#define BARWIDTH (ILI9341_TFTWIDTH - (NUMBARS + 1) * GAPWIDTH)/NUMBARS

void drawBarChart(fractional *, uint16_t);

inline fractional HEIGHT_fraction(uint16_t val) {
    // Just reverse the operations
    return val * (32769 / ILI9341_TFTHEIGHT);
}

inline uint16_t fraction_HEIGHT(fractional val) {
    // Just reverse the operations
    return val / (32769 / ILI9341_TFTHEIGHT);
}

fractional vals[NUMBARS];
uint16_t oldYs[NUMBARS];
uint16_t x[NUMBARS];

void barChartInit() {
    int i;
    for (i = 0; i < NUMBARS; i++){
        oldYs[i] = ILI9341_TFTHEIGHT;
        x[i] = GAPWIDTH + i * (GAPWIDTH + BARWIDTH);
    }

}

void drawBarChart(fractional *vals, uint16_t color){
    uint16_t index, newY,oldY, height;
    
    for (index = 0 ; index < NUMBARS; index++){
        height = fraction_HEIGHT(vals[index]);
        newY = ILI9341_TFTHEIGHT - height;
        oldY = oldYs[index];
        oldYs[index] = newY;
        
        if (oldY < newY){
            LCD_FillRect(x[index], oldY, BARWIDTH, newY - oldY, ILI9341_BLACK);
        }else{
            LCD_FillRect(x[index], newY, BARWIDTH, oldY - newY, color);
        }
    }
}

/**
 End of File
*/

