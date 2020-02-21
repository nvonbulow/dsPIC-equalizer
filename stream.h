/* 
 * File:   sampler.h
 * Author: nick
 *
 * Created on February 19, 2020, 10:53 AM
 */

#ifndef SAMPLER_H
#define	SAMPLER_H

#ifdef	__cplusplus
extern "C" {
#endif

// Sets the number of buffers
#define STREAM_BUFFER_COUNT 2
// Sets the size of the sample buffers
#define STREAM_BUFFER_SIZE 1024
    
// An interrupt is triggered on every secondary SCCP1 timer. This is the
// multiplier used on the secondary timer to reduce the number of interrupts
// produced. This might need to be adjusted so that the secondary timer counter
// does not exceed the limit of a 16 bit value
#define STREAM_OUTPUT_INTERRUPT_DIVIDER 16

// Future idea: if we run low on RAM, we should use two, maybe three buffers in
// total, them being shared by the input and output subsystems    

// Marked as volatile because the DMA controller writes to these
// The ADC input buffers
extern volatile uint16_t STREAM_input_buffers[STREAM_BUFFER_COUNT][STREAM_BUFFER_SIZE];

extern volatile int8_t STREAM_current_input_buffer;

extern volatile uint16_t STREAM_output_buffers[STREAM_BUFFER_COUNT][STREAM_BUFFER_SIZE];

extern volatile int8_t STREAM_current_output_buffer;

// The default sampling rate
#define STREAM_DEFAULT_SAMPLE_RATE 44100

// Sets up the ADC and DMA channels and the PTG to collect samples
void STREAM_Initialize(void);

void STREAM_InputEnable(void);

void STREAM_InputDisable(void);

void STREAM_SetSampleRate(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SAMPLER_H */

