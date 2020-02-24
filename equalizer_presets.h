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

fractional eq_presets[7][7] = {
    //popular =
    {
        Q15(0.8912509381337456f/1.4801083881682074f),
        Q15(1.0471285480508996f/1.4801083881682074f),
        Q15(1.4791083881682074f/1.4801083881682074f),
        Q15(1.4125375446227544f/1.4801083881682074f),
        Q15(1.0901844923851276f/1.4801083881682074f),
        Q15(0.9440608762859234f/1.4801083881682074f),
        Q15(1.1220184543019633f/1.4801083881682074f),
    },
    // blues =
    {
        Q15(1.9952623149688797f/1.9992623149688797f),
        Q15(1.318256738556407f/1.9992623149688797f),
        Q15(0.7585775750291838f/1.9992623149688797f),
        Q15(0.7943282347242815f/1.9992623149688797f),
        Q15(1.2589254117941673f/1.9992623149688797f),
        Q15(1.1885022274370185f/1.9992623149688797f),
        Q15(1.4125375446227544f/1.9992623149688797f),
    },
    // classical =
    {
        Q15(1.5848931924611136f/1.5908931924611136f),
        Q15(1.3489628825916538f/1.5908931924611136f),
        Q15(0.9549925860214359f/1.5908931924611136f),
        Q15(0.7943282347242815f/1.5908931924611136f),
        Q15(1.0292005271944282f/1.5908931924611136f),
        Q15(1.2589254117941673f/1.5908931924611136f),
        Q15(1.5848931924611136f/1.5908931924611136f),
    },
    // jazz =
    {
        Q15(1.4125375446227544f/1.5908931924611136f),
        Q15(1.1748975549395295f/1.5908931924611136f),
        Q15(0.8709635899560806f/1.5908931924611136f),
        Q15(0.8912509381337456f/1.5908931924611136f),
        Q15(1.0292005271944282f/1.5908931924611136f),
        Q15(1.1885022274370185f/1.5908931924611136f),
        Q15(1.5848931924611136f/1.5908931924611136f),
    },
    // electronic =
    {
        Q15(1.9952623149688797f/1.9992623149688797f),
        Q15(1.4125375446227544f/1.9992623149688797f),
        Q15(0.831763771102671f/1.9992623149688797f),
        Q15(1.1220184543019633f/1.9992623149688797f),
        Q15(1.0292005271944282f/1.9992623149688797f),
        Q15(1.333521432163324f/1.9992623149688797f),
        Q15(1.4125375446227544f/1.9992623149688797f),
    },
    // superbass =
    {
        Q15(1.7782794100389228f/2.24072113856834f),
        Q15(2.23872113856834f/2.24072113856834f),
        Q15(1.0592537251772889f/2.24072113856834f),
        Q15(1.0f/2.24072113856834f),
        Q15(1.0f/2.24072113856834f),
        Q15(1.0f/2.24072113856834f),
        Q15(1.0f/2.24072113856834f),
    },
    // lowpass =
    {
        Q15(0.999f),
        Q15(0.0f),
        Q15(0.0f),
        Q15(0.0f),
        Q15(0.0f),
        Q15(0.0f),
        Q15(0.0f),
    }};


#ifdef	__cplusplus
}
#endif

#endif	/* EQUALIZER_PRESETS_H */

