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
void adc_init (void)
{
    srand(time(NULL));
    previous_sample = rand();
    previous_sample = previous_sample>>4;
    // [ INSTRUMENTACION: Initialization event. ]
    pause(&reporting_clk);
    report(self_loggable_component_log_init_event,"adc");
    resume(&reporting_clk);
    //
}

// Sampling the ADC
int sample (void)
{
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
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
    // [ INSTRUMENTACION: Component event. ]
    pause(&reporting_clk);
    sprintf(str, "adc,%d",previous_sample);
    report(self_loggable_component_event,str);
    resume(&reporting_clk);
    //
    return previous_sample;
}
