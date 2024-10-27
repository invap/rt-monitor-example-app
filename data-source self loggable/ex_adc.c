#include <time.h>
#include <stdlib.h>

#include "ex_adc.h"

// Added to use the reporting API
#include "../../c-reporter-api/include/c-reporter-api.h"
#include "../../c-reporter-api/include/stopwatch.h"
//

// [ INSTRUMENTACION: Agregado para poder contabilizar el tiempo excluyendo el tiempo necesario para la instrumentación. ]
extern stopwatch reporting_clk;
//

// Initialization of the ADC
void adc_init (void){
    // [ INSTRUMENTACION: Initialization event. ]
    pause(&reporting_clk);
    report(self_loggable_component_log_init_event,"adc");
    resume(&reporting_clk);
    //
    file = fopen("./adc_info.csv","r");
    if (file == NULL) {
        adc_info_present = false;
    } else {
        adc_info_present = true;
        srand(time(NULL));
        previous_sample = rand();
        previous_sample = previous_sample>>4;
    }
}

// Sampling the ADC
int sample (void){
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    uint16_t sample;
    if (adc_info_present) {
        int result = fscanf(file, "%hd\n", &sample);
        // To check whether the data in the file was exhasted
        if (result != 1) {
            fprintf(stderr, "Error: Could not read sample from the file.\n");
            exit(-2);
        }
    } else {
        // The generation policy is that only 12 bits data is generated (0 <= sample < 4096) and
        // the new sample is only -16 < diff_sample < 16 (4 bits difference magnitude)
        uint16_t diff_sample = rand();
        int signo = (rand() % 2 == 0) ? 1 : -1;
        diff_sample = diff_sample >> 12;
        uint16_t datum = previous_sample + (signo * diff_sample);
        if (datum >= 0 && datum <= 4095)
            sample = datum;
        else
            if (datum > 4095)
                sample = 4095;
            else
                sample = 0;
        previous_sample = sample;
    }
    // [ INSTRUMENTACION: Component event. ]
    pause(&reporting_clk);
    sprintf(str, "adc,%d", sample);
    report(self_loggable_component_event,str);
    resume(&reporting_clk);
    //
    return sample;
}
