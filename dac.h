/* 
 * File:   dac.h
 * Author: nick
 *
 * Created on February 19, 2020, 3:20 PM
 */

#ifndef DAC_H
#define	DAC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define DAC_VoltageToValue(mv) (((uint32_t)4095*mv/3300) & 0x0FFF)

// Enables the operation of the DAC
void DAC_Enable(void);

// Disables the operation of the DAC
void DAC_Disable(void);

// Sets the DAC voltage in millivolts
void DAC_SetVoltage(uint16_t mv);

#ifdef	__cplusplus
}
#endif

#endif	/* DAC_H */

