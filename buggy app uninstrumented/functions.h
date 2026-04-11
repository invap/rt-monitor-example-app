#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

#include "../data-display/ex_display.h"
#include "../data-display/rgb.h"

void drawImage2Color_HSB8(uint16_t, uint16_t, uint8_t const *, const rgb *,  const rgb*);
void measurement(int16_t);
void bar( int16_t, int16_t);
void background(void);

#endif
