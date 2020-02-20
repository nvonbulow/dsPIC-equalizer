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
#define SAMPLER_BUFFER_COUNT 2
// Sets the size of the sample buffers
#define SAMPLER_BUFFER_SIZE 1024

// Marked as volatile because the DMA controller writes to these
// The ADC input buffers
extern volatile uint16_t sample_buffer[SAMPLER_BUFFER_COUNT][SAMPLER_BUFFER_SIZE];

// The default sampling rate
#define SAMPLER_DEFAULT_RATE 44100

// Sets up the ADC and DMA channels and the PTG to collect samples
void STREAM_Initialize(void);

void STREAM_Enable(void);

void SAMPER_Disable(void);

void SAMPLER_SetSampleRate(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SAMPLER_H */

