
#include <dsp.h>
#include <stdint.h>

#include "ui.h"

#include "lcd_ILI9341.h"

#define NUMBARS 7
#define GAPWIDTH 5
#define BARWIDTH (ILI9341_TFTWIDTH - (NUMBARS + 1) * GAPWIDTH)/NUMBARS

static inline fractional HeightToFrac(uint16_t val) {
    // Just reverse the operations
    return val * (32769 / ILI9341_TFTHEIGHT);
}

static inline uint16_t FractToHeight(fractional val) {
    // Just reverse the operations
    return val / (32769 / ILI9341_TFTHEIGHT);
}

fractional vals[NUMBARS];
uint16_t oldYs[NUMBARS];
uint16_t x[NUMBARS];

void UI_AudioInit() {
    int i;
    for (i = 0; i < NUMBARS; i++){
        oldYs[i] = ILI9341_TFTHEIGHT;
        x[i] = GAPWIDTH + i * (GAPWIDTH + BARWIDTH);
    }

}

void UI_DrawBarChart(const fractional *vals, uint16_t color) {
    uint16_t index, newY,oldY, height;
    
    for (index = 0 ; index < NUMBARS; index++){
        height = FractToHeight(vals[index]);
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