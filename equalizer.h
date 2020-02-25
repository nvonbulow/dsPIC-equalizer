/* 
 * File:   equalizer.h
 * Author: Nick von Bulow
 *
 * Created on February 25, 2020, 11:47 AM
 */

#ifndef EQUALIZER_H
#define	EQUALIZER_H

#include <dsp.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

void EQUALIZER_Initialize();

void EQUALIZER_CoeffBandGain(fractional *dst, const fractional **bands, const fractional *gains, uint16_t num_bands);

void EQUALIZER_SetEqPreset(uint8_t preset);

void EQUALIZER_SetBandGains(const fractional* gains);

void EQUALIZER_Apply(uint16_t *out, uint16_t *in);


#ifdef	__cplusplus
}
#endif

#endif	/* EQUALIZER_H */

