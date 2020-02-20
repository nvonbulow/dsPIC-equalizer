
#include <stdint.h>
#include <xc.h>

#include "dac.h"

void DAC_Enable() {
    DAC1CONLbits.DACOEN = 1;
    DAC1CONLbits.DACEN = 1;
    DACCTRL1Lbits.DACON = 1;
}

void DAC_Disable() {
    DAC1CONLbits.DACOEN = 0;
    DAC1CONLbits.DACEN = 0;
    DACCTRL1Lbits.DACON = 0;
}

// VDAC = DACDAT * (AVDD)/4095
// DACDAT = 4095*VDAC/AVDD
// Sets the DAC voltage in millivolts
void DAC_SetVoltage(uint16_t mv) {
    DAC1DATH = ((uint32_t)4095*mv/3300) & 0x0FFF;
}
