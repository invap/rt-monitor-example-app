#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// To discriminate whether adc data is read from file or generated
bool adc_info_present;
// For when adc data is read from file
FILE *file;
// For when adc data is generated
uint16_t previous_sample;

void adc_init (void);
int sample (void);

#endif
