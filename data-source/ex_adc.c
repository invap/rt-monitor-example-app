#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "ex_adc.h"

// To discriminate whether adc data is read from file or generated
bool adc_info_present;
// For when adc data is read from file
FILE *file;
// For when adc data is generated
uint16_t previous_sample;


// Initialization of the ADC
void adc_init (void){
    file = fopen("./adc_info.csv","r");
    if (file != NULL)
        adc_info_present = true;
    else {
        adc_info_present = false;
        srand(time(NULL));
        previous_sample = rand();
        previous_sample = previous_sample>>4;
    }
}

// Sampling the ADC
int sample (void){
    if (adc_info_present) {
        uint16_t sample;
        int result = fscanf(file, "%hd\n", &sample);
        // To check whether the data in the file was exhasted
        if (result != 1) {
            fprintf(stderr, "Error: Could not read sample from the file.\n");
            exit(-2);
        }
        return sample;
    } else {
        // The generation policy is that only 12 bits data is generated (0 <= sample < 4096) and
        // the new sample is only -16 < diff_sample < 16 (4 bits difference magnitude)
        uint16_t diff_sample = rand();
        int signo = (rand() % 2 == 0) ? 1 : -1;
        diff_sample = diff_sample >> 12;
        uint16_t datum = previous_sample + (signo * diff_sample);
        if (datum >= 0 && datum <= 4095)
            previous_sample = datum;
        else if (datum > 4095)
            previous_sample = 4095;
        else
            previous_sample = 0;
        return previous_sample;
    }
}
