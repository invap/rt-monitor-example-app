#include <time.h>
#include <stdlib.h>

#include "ex_adc.h"

// Initialization of the ADC
void adc_init (void)
{
    srand(time(NULL));
    previous_sample = rand();
    previous_sample = previous_sample>>4;
}

// Sampling the ADC
int sample (void)
{
    uint16_t diff_sample = rand();
    int signo = (rand()%2==0) ? 1 : -1;
    diff_sample = diff_sample>>12;
    uint16_t datum = previous_sample+(signo*diff_sample);
    if (datum >= 0 && datum <= 4095 )
        previous_sample = datum;
    else
        if (datum > 4095)
            previous_sample = 4095;
        else
            previous_sample = 0;
	return previous_sample;
}
