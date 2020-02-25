/* 
 * File:   equalizer_presets.h
 * Author: nick
 *
 * Created on February 24, 2020, 3:45 AM
 */

#ifndef EQUALIZER_PRESETS_H
#define	EQUALIZER_PRESETS_H

#include <dsp.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
#define NUMFILTERS 10
    
#define EQ_NORMAL 0
#define EQ_POPULAR 1
#define EQ_BLUES 2
#define EQ_CLASSICAL 3
#define EQ_JAZZ 4
#define EQ_ELECTRONIC 5
#define EQ_SUPERBASS 6
#define EQ_LOWPASS 7
#define EQ_HIGHPASS 8
#define EQ_BANDPASS 9

extern const fractional eq_presets[NUMFILTERS][7];


#ifdef	__cplusplus
}
#endif

#endif	/* EQUALIZER_PRESETS_H */

