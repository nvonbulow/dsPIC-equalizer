/* 
 * File:   ui.h
 * Author: Nick von Bulow
 *
 * Created on February 25, 2020, 11:43 AM
 */

#ifndef UI_H
#define	UI_H

#include <dsp.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif


void UI_AudioInit();

void UI_ImageInit();

void UI_DrawBarChart(const fractional *vals, uint16_t color);

void UI_DrawImage();

#ifdef	__cplusplus
}
#endif

#endif	/* UI_H */

