#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../data-source/ex_adc.h"
#include "functions.h"

// Added to use the reporting API
#include "../../c-reporter-api/include/c-reporter-api.h"
#include "../../timer/include/timer.h"
//

// [ INSTRUMENTACION: Agregado para poder contabilizar el tiempo excluyendo el tiempo necesario para la instrumentación. ]
extern timer reporting_clk;
//

int main( void ){
    // [ INSTRUMENTACION: Inicialización del timer. ]
    start (&reporting_clk);
    //
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    // [ INSTRUMENTATION: Declare variables. ]
    // Declaración de las variables de programa
    pause(&reporting_clk);
    sprintf(str, "declare_variable,main_addition,uint16_t");
    report(workflow_event,str);
    sprintf(str, "declare_variable,main_adc_read,uint16_t");
    report(workflow_event,str);
    for (int16_t i=0;i<16; i++) {
        sprintf(str, "declare_variable,main_value_%d,uint16_t",i);
        report(workflow_event,str);
    }
    sprintf(str, "declare_variable,main_realvalue,uint16_t");
    report(workflow_event,str);
    sprintf(str, "declare_variable,main_realvalue_old,uint16_t");
    report(workflow_event,str);
    sprintf(str, "declare_variable,measurement_dato_ing,float");
    report(workflow_event,str);
    sprintf(str, "declare_variable,measurement_dato_ing2,float");
    report(workflow_event,str);
    sprintf(str, "declare_variable,bar_dato_ing,float");
    report(workflow_event,str);
    sprintf(str, "declare_variable,bar_point,int");
    report(workflow_event,str);
    resume(&reporting_clk);
    //
    uint16_t realvalue_old, value, addition, realvalue;
    // [ INSTRUMENTACION: Task "init" started. ]
    pause(&reporting_clk);
    report(workflow_event,"task_started,init");
    resume(&reporting_clk);
    //
    adc_init ();
    background();
    // [ POTENTIAL PROBLEM FOUND: realvalue_old was not initialized.  ]
    realvalue_old = 0;
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&reporting_clk);
    sprintf(str, "variable_value_assigned,main_realvalue_old,%d", realvalue_old);
    report(workflow_event,str);
    resume(&reporting_clk);
    //
    // [ INSTRUMENTACION: Task "init" finished. ]
    pause(&reporting_clk);
    report(workflow_event,"task_finished,init");
    resume(&reporting_clk);
    //
    while (1) {
        addition = 0;
        // [ INSTRUMENTACION: Variable assigned. ]
        pause(&reporting_clk);
        sprintf(str, "variable_value_assigned,main_addition,%d", addition);
        report(workflow_event,str);
        resume(&reporting_clk);
        //
        // [ INSTRUMENTACION: Task "filtering" started. ]
        pause(&reporting_clk);
        report(workflow_event,"task_started,filtering");
        resume(&reporting_clk);
        //
        for (int16_t i=0;i<16; i++){
            value = sample ();
            // [ INSTRUMENTACION: Component event. ]
            pause(&reporting_clk);
            sprintf(str, "adc,sample,%d",value);
            report(component_event,str);
            resume(&reporting_clk);
            //
            // [ INSTRUMENTACION: Variable assigned. ]
            pause(&reporting_clk);
            sprintf(str, "variable_value_assigned,main_adc_read,%d",value);
            report(workflow_event,str);
            resume(&reporting_clk);
            //
            // [ INSTRUMENTACION: Variable assigned. ]
            pause(&reporting_clk);
            sprintf(str, "variable_value_assigned,main_value_%d,%d",i,value);
            report(workflow_event,str);
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
            report(workflow_event,str);
            resume(&reporting_clk);
            //
        }
        realvalue = addition/16;
        // [ INSTRUMENTACION: Variable assigned. ]
        pause(&reporting_clk);
        sprintf(str, "variable_value_assigned,main_realvalue,%d", realvalue);
        report(workflow_event,str);
        resume(&reporting_clk);
        //
        // [ INSTRUMENTACION: Task "filtering" finished. ]
        pause(&reporting_clk);
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
        report(workflow_event,str);
        resume(&reporting_clk);
        //
        // [ INSTRUMENTACION: Checkpoint filtering_chk alcanzado. ]
        pause(&reporting_clk);
        report(workflow_event,"checkpoint_reached,display_chk");
        resume(&reporting_clk);
        //
	} // WHILE
} // MAIN
