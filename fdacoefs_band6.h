/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.7 and DSP System Toolbox 9.9.
 * Generated on: 24-Feb-2020 02:25:07
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 251
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 * Arithmetic        : fixed
 * Numerator         : s16,15 -> [-1 1)
 * Input             : s16,15 -> [-1 1)
 * Filter Internals  : Specify Precision
 *   Output          : s16,15 -> [-1 1)
 *   Product         : s40,31 -> [-256 256)
 *   Accumulator     : s40,31 -> [-256 256)
 *   Round Mode      : convergent
 *   Overflow Mode   : wrap
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\R2019b\extern\include\tmwtypes.h 
 */
const int BL = 251;
const int16_T B[251] = {
       -1,      0,     -5,     -3,      9,     14,      6,     -4,     -2,
        3,     -4,    -16,    -13,      4,     12,      5,      0,     11,
       19,      3,    -20,    -20,     -3,     -1,    -15,    -12,     19,
       38,     19,     -8,     -4,     11,     -8,    -46,    -43,      4,
       31,     12,     -1,     33,     60,     18,    -50,    -56,    -11,
       -5,    -47,    -42,     42,    102,     57,    -14,     -4,     37,
      -11,   -115,   -120,     -6,     68,     23,     -9,     78,    157,
       66,   -102,   -129,    -29,    -14,   -120,   -122,     72,    227,
      142,    -16,      5,    105,      2,   -246,   -287,    -46,    128,
       36,    -38,    161,    365,    192,   -183,   -271,    -64,    -32,
     -285,   -326,     99,    486,    341,     -6,     40,    289,     74,
     -539,   -712,   -183,    251,     46,   -150,    366,    983,    632,
     -377,   -705,   -167,    -79,   -926,  -1225,    115,   1643,   1363,
       76,    290,   1734,    883,  -3451,  -6586,  -3202,   4746,   8978,
     4746,  -3202,  -6586,  -3451,    883,   1734,    290,     76,   1363,
     1643,    115,  -1225,   -926,    -79,   -167,   -705,   -377,    632,
      983,    366,   -150,     46,    251,   -183,   -712,   -539,     74,
      289,     40,     -6,    341,    486,     99,   -326,   -285,    -32,
      -64,   -271,   -183,    192,    365,    161,    -38,     36,    128,
      -46,   -287,   -246,      2,    105,      5,    -16,    142,    227,
       72,   -122,   -120,    -14,    -29,   -129,   -102,     66,    157,
       78,     -9,     23,     68,     -6,   -120,   -115,    -11,     37,
       -4,    -14,     57,    102,     42,    -42,    -47,     -5,    -11,
      -56,    -50,     18,     60,     33,     -1,     12,     31,      4,
      -43,    -46,     -8,     11,     -4,     -8,     19,     38,     19,
      -12,    -15,     -1,     -3,    -20,    -20,      3,     19,     11,
        0,      5,     12,      4,    -13,    -16,     -4,      3,     -2,
       -4,      6,     14,      9,     -3,     -5,      0,     -1
};
