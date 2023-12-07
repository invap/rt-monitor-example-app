#ifndef ADC_H
#define ADC_H

#include <stdint.h>

uint16_t previous_sample;

void adc_init (void);
int sample (void);

#endif
