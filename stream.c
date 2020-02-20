#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "mcc_generated_files/dma.h"
#include "mcc_generated_files/ptg.h"

#include "stream.h"

volatile uint16_t sample_buffer[SAMPLER_BUFFER_COUNT][SAMPLER_BUFFER_SIZE];

uint8_t current_buffer = 0;

static volatile bool buffer_ready = false;

void STREAM_Initialize() {
    // The source address remains the same as we copy from the adc buffer always
    // Because the DMA controller is triggered by the ADC convert done, we don't
    // need to check if the convert is done
    DMA_SourceAddressSet(DMA_CHANNEL_0, (uint16_t) &ADCBUF0);
}

void STREAM_Enable() {
    // The destination address base
    DMA_DestinationAddressSet(DMA_CHANNEL_0, (uint16_t) sample_buffer[current_buffer]);
    DMA_TransferCountSet(DMA_CHANNEL_0, SAMPLER_BUFFER_SIZE);
    DMA_ChannelEnable(DMA_CHANNEL_0);
    PTG_Enable();
    PTG_StartStepSequence();
}

void STREAM_Disable() {
    PTG_StopStepSequence();
    PTG_Disable();
    DMA_ChannelDisable(DMA_CHANNEL_0);
}

bool STREAM_BufferReady() {
    if(buffer_ready) {
        buffer_ready = false;
        return true;
    }
    return false;
}

void PTG_Trigger0_CallBack(void) {
    if(++current_buffer >= SAMPLER_BUFFER_COUNT) {
        // start over
        current_buffer = 0;
    }
    // Swap buffers and start PTG again
    DMA_ChannelDisable(DMA_CHANNEL_0);
    DMA_DestinationAddressSet(DMA_CHANNEL_0, (uint16_t) sample_buffer[current_buffer]);
    DMA_TransferCountSet(DMA_CHANNEL_0, SAMPLER_BUFFER_SIZE);
    DMA_ChannelEnable(DMA_CHANNEL_0);
    // Let PTG know to resume again
    PTG_SoftwareTriggerSet();
    
    buffer_ready = true;
}
