
#include <dsp.h>

#include "lcd_ILI9341.h"

#define NUMBARS 7
#define GAPWIDTH 5
#define BARWIDTH (ILI9341_TFTWIDTH - (NUMBARS + 1) * GAPWIDTH)/NUMBARS

void drawBarChart(fractional *, uint16_t);

inline fractional HEIGHT_fraction(uint16_t val) {
    // Just reverse the operations
    return val * (32769 / ILI9341_TFTHEIGHT);
}

inline uint16_t fraction_HEIGHT(fractional val) {
    // Just reverse the operations
    return val / (32769 / ILI9341_TFTHEIGHT);
}

fractional vals[NUMBARS];
uint16_t oldYs[NUMBARS];
uint16_t x[NUMBARS];

void barChartInit() {
    int i;
    for (i = 0; i < NUMBARS; i++){
        oldYs[i] = ILI9341_TFTHEIGHT;
        x[i] = GAPWIDTH + i * (GAPWIDTH + BARWIDTH);
    }

}

void drawBarChart(fractional *vals, uint16_t color){
    uint16_t index, newY,oldY, height;
    
    for (index = 0 ; index < NUMBARS; index++){
        height = fraction_HEIGHT(vals[index]);
        newY = ILI9341_TFTHEIGHT - height;
        oldY = oldYs[index];
        oldYs[index] = newY;
        
        if (oldY < newY){
            LCD_FillRect(x[index], oldY, BARWIDTH, newY - oldY, ILI9341_BLACK);
        }else{
            LCD_FillRect(x[index], newY, BARWIDTH, oldY - newY, color);
        }
    }
}