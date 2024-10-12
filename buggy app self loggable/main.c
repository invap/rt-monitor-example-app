#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../data-source self loggable/ex_adc.h"
#include "functions.h"

// Added to use the reporting API
#include "../../c-reporter-api/include/c-reporter-api.h"
#include "../../c-reporter-api/include/stopwatch.h"
//

// [ INSTRUMENTACION: Agregado para poder contabilizar el tiempo excluyendo el tiempo necesario para la instrumentación. ]
extern stopwatch reporting_clk;
//

int main( void ){
    // [ INSTRUMENTACION: Inicialización del timer. ]
    start (&reporting_clk);
    //
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    uint16_t realvalue_old, value, addition, realvalue;
    // [ INSTRUMENTACION: Task "init" started. ]
    pause(&reporting_clk);
    report(workflow_event,"task_started,init");
    report(timed_event,"clock_start,init_clk");
    resume(&reporting_clk);
    //
    adc_init ();
    background();
    // [ POTENTIAL PROBLEM FOUND: realvalue_old was not initialized.  ]
    realvalue_old = 0;
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&reporting_clk);
    sprintf(str, "variable_value_assigned,main_realvalue_old,%d", realvalue_old);
    report(state_event,str);
    report(timed_event,"clock_pause,init_clk");
    resume(&reporting_clk);
    //
    // [ INSTRUMENTACION: Task "init" finished. ]
    pause(&reporting_clk);
    report(workflow_event,"task_finished,init");
    report(timed_event,"clock_start,filtering_clk");
    report(timed_event,"clock_pause,filtering_clk");
    resume(&reporting_clk);
    //
    while (1) {
        addition = 0;
        // [ INSTRUMENTACION: Variable assigned. ]
        pause(&reporting_clk);
        sprintf(str, "variable_value_assigned,main_addition,%d", addition);
        report(state_event,str);
        resume(&reporting_clk);
        //
        // [ INSTRUMENTACION: Task "filtering" started. ]
        pause(&reporting_clk);
        report(workflow_event,"task_started,filtering");
        report(timed_event,"clock_reset,filtering_clk");
        resume(&reporting_clk);
        //
        for (int16_t i=0;i<16; i++){
            value = sample ();
            // [ INSTRUMENTACION: Variable assigned. ]
            pause(&reporting_clk);
            sprintf(str, "variable_value_assigned,main_value_%d,%d",i,value);
            report(state_event,str);
            resume(&reporting_clk);
            //
            // [ INSTRUMENTACION: Checkpoint filtering_chk alcanzado. ]
            pause(&reporting_clk);
            report(workflow_event,"checkpoint_reached,filtering_chk");
            resume(&reporting_clk);
            //
            addition = addition + value;
            // [ INSTRUMENTACION: Variable assigned. ]
            pause(&reporting_clk);
            sprintf(str, "variable_value_assigned,main_addition,%d", addition);
            report(state_event,str);
            resume(&reporting_clk);
            //
        }
        realvalue = addition/16;
        // [ INSTRUMENTACION: Variable assigned. ]
        pause(&reporting_clk);
        sprintf(str, "variable_value_assigned,main_realvalue,%d", realvalue);
        report(state_event,str);
        resume(&reporting_clk);
        //
        // [ INSTRUMENTACION: Task "filtering" finished. ]
        pause(&reporting_clk);
        report(timed_event,"clock_pause,filtering_clk");
        report(workflow_event,"task_finished,filtering");
        resume(&reporting_clk);
        //
        // [ INSTRUMENTACION: Task "conversion" started. ]
        pause(&reporting_clk);
        report(workflow_event,"task_started,conversion");
        resume(&reporting_clk);
        //
        measurement(realvalue);
        bar(realvalue, realvalue_old);
        // [ INSTRUMENTACION: Task "conversion" finished. ]
        pause(&reporting_clk);
        report(workflow_event,"task_finished,conversion");
        resume(&reporting_clk);
        //
        realvalue_old = realvalue;
        // [ INSTRUMENTACION: Variable assigned. ]
        pause(&reporting_clk);
        sprintf(str, "variable_value_assigned,main_realvalue_old,%d", realvalue_old);
        report(state_event,str);
        resume(&reporting_clk);
        //
        // [ INSTRUMENTACION: Checkpoint filtering_chk alcanzado. ]
        pause(&reporting_clk);
        report(workflow_event,"checkpoint_reached,display_chk");
        resume(&reporting_clk);
        //
	} // WHILE
} // MAIN
