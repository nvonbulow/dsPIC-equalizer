#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "mcc_generated_files/clock.h"
#include "mcc_generated_files/dma.h"
#include "mcc_generated_files/ptg.h"
#include "mcc_generated_files/sccp1_tmr.h"

#include "dac.h"
#include "stream.h"

volatile uint16_t STREAM_input_buffers[STREAM_BUFFER_COUNT][STREAM_BUFFER_SIZE];

volatile uint8_t STREAM_current_input_buffer = 0;

volatile uint16_t STREAM_output_buffers[STREAM_BUFFER_COUNT][STREAM_BUFFER_SIZE];

volatile uint8_t STREAM_current_output_buffer;

static volatile bool input_buffer_ready = false;

static volatile bool output_buffer_written = false;

void STREAM_Initialize() {
    // The source address remains the same as we copy from the adc buffer always
    // Because the DMA controller is triggered by the ADC convert done, we don't
    // need to check if the convert is done
    DMA_SourceAddressSet(DMA_CHANNEL_0, (uint16_t) &ADCBUF0);
    // For the output, the destination address is always the DAC output register
    DMA_DestinationAddressSet(DMA_CHANNEL_1, (uint16_t) &DAC1DATH);
    // PTG Timer Limit = Fosc/2 * t = Fosc/2 * 1/f
    PTGT0LIM = _XTAL_FREQ / (2 * STREAM_DEFAULT_SAMPLE_RATE);
    // Primary SCCP timer counter uses the same formula
    SCCP1_TMR_Period16BitPrimarySet(_XTAL_FREQ / (2 * STREAM_DEFAULT_SAMPLE_RATE));
    // Set the secondary period counter to be a multiple of the primary
    SCCP1_TMR_Period16BitSecondarySet(_XTAL_FREQ * STREAM_OUTPUT_INTERRUPT_DIVIDER / (2 * STREAM_DEFAULT_SAMPLE_RATE));
}

void STREAM_InputEnable() {
    // The destination address base
    DMA_DestinationAddressSet(DMA_CHANNEL_0, (uint16_t) STREAM_input_buffers[STREAM_current_input_buffer]);
    DMA_TransferCountSet(DMA_CHANNEL_0, STREAM_BUFFER_SIZE);
    DMA_ChannelEnable(DMA_CHANNEL_0);
    PTG_Enable();
    PTG_StartStepSequence();
}

void STREAM_OutputEnable() {
    DMA_SourceAddressSet(DMA_CHANNEL_1, (uint16_t) STREAM_output_buffers[STREAM_current_output_buffer]);
    DMA_TransferCountSet(DMA_CHANNEL_1, STREAM_BUFFER_SIZE);
    SCCP1_TMR_Start();
    DAC_Enable();
}

void STREAM_InputDisable() {
    PTG_StopStepSequence();
    PTG_Disable();
    DMA_ChannelDisable(DMA_CHANNEL_0);
}

void STREAM_OutputDisable() {
    DAC_Disable();
    SCCP1_TMR_Stop();
    DMA_ChannelDisable(DMA_CHANNEL_1);
}

uint16_t* STREAM_GetNextInputBuffer() {
    if(STREAM_current_input_buffer + 1 >= STREAM_BUFFER_COUNT) {
        return STREAM_input_buffers[0];
    }
    return STREAM_input_buffers[STREAM_current_input_buffer];
}

uint16_t* STREAM_GetNextOutputBuffer() {
    if(STREAM_current_output_buffer + 1 >= STREAM_BUFFER_COUNT) {
        return STREAM_output_buffers[0];
    }
    return STREAM_output_buffers[STREAM_current_output_buffer];
}

bool STREAM_InputBufferReady() {
    if(input_buffer_ready) {
        input_buffer_ready = false;
        return true;
    }
    return false;
}

bool STREAM_OutputBufferWritten() {
    if(output_buffer_written) {
        output_buffer_written = false;
        return true;
    }
    return false;
}

// This interrupt is triggered when the PTG completes 1024 samples, so we can
// change out the buffer and reset the PTG/DMA controller
void PTG_Trigger0_CallBack(void) {
    if(++STREAM_current_input_buffer >= STREAM_BUFFER_COUNT) {
        // start over
        STREAM_current_input_buffer = 0;
    }
    // Swap buffers and start PTG again
    DMA_ChannelDisable(DMA_CHANNEL_0);
    DMA_DestinationAddressSet(DMA_CHANNEL_0, (uint16_t) STREAM_input_buffers[STREAM_current_input_buffer]);
    DMA_TransferCountSet(DMA_CHANNEL_0, STREAM_BUFFER_SIZE);
    DMA_ChannelEnable(DMA_CHANNEL_0);
    // Let PTG know to resume again
    PTG_SoftwareTriggerSet();
    
    input_buffer_ready = true;
}

// This interrupt is triggered when the secondary timer period on the CCP module
// expires. This is set to a multiple of the actual sample rate. We need to count
// The number of times this interrupt is called and reset the timer and DMA buffer
// when all the samples from the current buffer have been written to the DAC
void SCCP1_TMR_SecondaryTimerCallBack(void) {
    static int call_count = 0;
    if(++call_count == STREAM_BUFFER_SIZE / STREAM_OUTPUT_INTERRUPT_DIVIDER) {
        call_count = 0;
        if(++STREAM_current_output_buffer >= STREAM_BUFFER_COUNT) {
            STREAM_current_output_buffer = 0;
        }
        // Swap buffers and reset DMA
        DMA_ChannelDisable(DMA_CHANNEL_1);
        DMA_SourceAddressSet(DMA_CHANNEL_1, (uint16_t) STREAM_output_buffers[STREAM_current_output_buffer]);
        DMA_TransferCountSet(DMA_CHANNEL_1, STREAM_BUFFER_SIZE);
        DMA_ChannelEnable(DMA_CHANNEL_1);
        
        output_buffer_written = true;
    }
}