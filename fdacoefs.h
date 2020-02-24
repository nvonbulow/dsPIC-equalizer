/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.7 and DSP System Toolbox 9.9.
 * Generated on: 23-Feb-2020 11:42:01
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 224
 * Stable            : Yes
 * Linear Phase      : Yes (Type 2)
 * Arithmetic        : fixed
 * Numerator         : s16,15 -> [-1 1)
 * Input             : s16,15 -> [-1 1)
 * Filter Internals  : Specify Precision
 *   Output          : s16,12 -> [-8 8)
 *   Product         : s40,31 -> [-256 256)
 *   Accumulator     : s40,31 -> [-256 256)
 *   Round Mode      : convergent
 *   Overflow Mode   : saturate
 */

/* General type conversion for MATLAB generated C-code  */
#include <dsp.h>
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\R2019b\extern\include\tmwtypes.h 
 */
const int BL = 224;
fractional B[224] __attribute__((space (xmemory))) = {
        3,      3,      4,      6,      7,      9,     12,     15,     18,
       21,     25,     29,     33,     37,     41,     45,     49,     52,
       56,     58,     60,     61,     62,     61,     59,     56,     52,
       46,     39,     31,     21,     11,     -1,    -13,    -26,    -39,
      -52,    -65,    -78,    -90,   -100,   -109,   -117,   -122,   -125,
     -126,   -123,   -119,   -111,   -101,    -88,    -72,    -55,    -35,
      -14,      7,     30,     52,     73,     93,    112,    127,    140,
      149,    153,    154,    149,    140,    125,    106,     81,     52,
       20,    -16,    -55,    -95,   -137,   -178,   -217,   -254,   -287,
     -315,   -337,   -352,   -359,   -356,   -344,   -321,   -287,   -242,
     -186,   -119,    -41,     46,    143,    247,    357,    473,    593,
      714,    836,    956,   1072,   1183,   1287,   1382,   1466,   1539,
     1599,   1644,   1675,   1691,   1691,   1675,   1644,   1599,   1539,
     1466,   1382,   1287,   1183,   1072,    956,    836,    714,    593,
      473,    357,    247,    143,     46,    -41,   -119,   -186,   -242,
     -287,   -321,   -344,   -356,   -359,   -352,   -337,   -315,   -287,
     -254,   -217,   -178,   -137,    -95,    -55,    -16,     20,     52,
       81,    106,    125,    140,    149,    154,    153,    149,    140,
      127,    112,     93,     73,     52,     30,      7,    -14,    -35,
      -55,    -72,    -88,   -101,   -111,   -119,   -123,   -126,   -125,
     -122,   -117,   -109,   -100,    -90,    -78,    -65,    -52,    -39,
      -26,    -13,     -1,     11,     21,     31,     39,     46,     52,
       56,     59,     61,     62,     61,     60,     58,     56,     52,
       49,     45,     41,     37,     33,     29,     25,     21,     18,
       15,     12,      9,      7,      6,      4,      3,      3
};