
#include <dsp.h>
#include <stdbool.h>
#include <string.h>

#include "equalizer_presets.h"
#include "fdacoefs_bands.h"
#include "stream.h"

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

static inline fractional U12_Q15(uint16_t val) {
    // Data is in the range 0..4096, which is 12 bits
    // We want it in the range -0.5..0.5
    // We'll normalize the data so it's in the range 0..1 by shifting left
    // 3 bits (fractional is bits 0..14), and then subtract 0.5 to get it in
    // the -0.5..0.5 range
    return (val << 3) - Q15(0.5f);
}

static inline uint16_t Q15_U12(fractional val) {
    // Just reverse the operations
    return (val + Q15(0.5f)) >> 3;
}

void EQUALIZER_Initialize() {
    // FIR filter setup
    // Uses coefficents defined in main.c
    // FIRStructInit(&filter, sizeof(filter_coeffs) / sizeof(fractional), filter_coeffs, COEFFS_IN_DATA, filter_delay);
    // Uses coefficients in fdacoefs.h (generated by MATLAB)
    FIRStructInit(&filter, NUM_COEFFS, filter_coeffs, COEFFS_IN_DATA, filter_delay);
    FIRDelayInit(&filter);
}

void EQUALIZER_CoeffBandGain(fractional *dst, const fractional **bands, const fractional *gains, uint16_t num_bands) {
    int i;
    fractional coeff_buffer[NUM_COEFFS];
    
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

void EQUALIZER_SetEqPreset(uint8_t current_preset) {
    EQUALIZER_SetBandGains(eq_presets[current_preset]);
}

void EQUALIZER_SetBandGains(const fractional *gains) {
    EQUALIZER_CoeffBandGain(filter_coeffs, BANDS, gains, NUM_BANDS);
}

void EQUALIZER_Apply(uint16_t *out, uint16_t *in) {
    int i;
    
    // convert input data to Q15 format
    for(i = 0; i < STREAM_BUFFER_SIZE; i++) {
        filter_in[i] = U12_Q15(in[i]);
    }
    
    // Apply the filter
    FIR(STREAM_BUFFER_SIZE, filter_out, filter_in, &filter);

    // convert output data to U12 format
    for(i = 0; i < STREAM_BUFFER_SIZE; i++) {
        out[i] = Q15_U12(filter_out[i]);
    }
}