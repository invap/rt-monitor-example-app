#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "./data-source/ex_adc.h"
#include "functions.h"

// Added to use the reporting API
#include "../c-reporter-api/src/c-reporter-api.h"

int main( void ){
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[1024];
    //
    // [ INSTRUMENTATION: Declare variables. ]
    // Declaración de las variables de programa
    sprintf(str, "declare_variable,main_addition,uint16_t");
    report(clock(),workflow_event,str);
    for (int16_t i=0;i<16; i++) {
        sprintf(str, "declare_variable,main_value_%d,uint16_t",i);
        report(clock(),workflow_event,str);
    }
    sprintf(str, "declare_variable,main_realvalue,uint16_t");
    report(clock(),workflow_event,str);
    sprintf(str, "declare_variable,main_realvalue_old,uint16_t");
    report(clock(),workflow_event,str);
    sprintf(str, "declare_variable,measurement_dato_ing,float");
    report(clock(),workflow_event,str);
    sprintf(str, "declare_variable,measurement_dato_ing2,float");
    report(clock(),workflow_event,str);
    sprintf(str, "declare_variable,bar_dato_ing,float");
    report(clock(),workflow_event,str);
    sprintf(str, "declare_variable,bar_point,int");
    report(clock(),workflow_event,str);
    //
    // [ INSTRUMENTACION: Task "init" started. ]
    report(clock(),workflow_event,"task_started,init");
    //
    adc_init ();
    background();
    // [ INSTRUMENTACION: Task "init" finished. ]
    report(clock(),workflow_event,"task_finished,init");
    //
    while (1) {
        uint16_t addition;
        uint16_t value;
        uint16_t realvalue;
        uint16_t  realvalue_old = 0;
        // [ INSTRUMENTACION: Variable assigned. ]
        sprintf(str, "variable_value_assigned,main_realvalue_old,%d", realvalue_old);
        report(clock(),workflow_event,str);
        //
        addition = 0;
        // [ INSTRUMENTACION: Variable assigned. ]
        sprintf(str, "variable_value_assigned,main_addition,%d", addition);
        report(clock(),workflow_event,str);
        //
        // [ INSTRUMENTACION: Task "filtering" started. ]
        report(clock(),workflow_event,"task_started,filtering");
        //
        for (int16_t i=0;i<16; i++){
            value = sample ();
            // [ INSTRUMENTACION: Hardware event - adc read. ]
            sprintf(str, "adc,sample,%d",value);
            report(clock(),hardware_event,str);
            //
            // [ INSTRUMENTACION: Variable assigned. ]
            sprintf(str, "variable_value_assigned,main_value_%d,%d",i,value);
            report(clock(),workflow_event,str);
            //
            // [ INSTRUMENTACION: Checkpoint filtering_chk alcanzado. ]
            report(clock(),workflow_event,"checkpoint_reached,filtering_chk");
            //
            addition = addition + value;
            // [ INSTRUMENTACION: Variable assigned. ]
            sprintf(str, "variable_value_assigned,main_addition,%d", addition);
            report(clock(),workflow_event,str);
            //
        }
        realvalue = addition/16;
        // [ INSTRUMENTACION: Variable assigned. ]
        sprintf(str, "variable_value_assigned,main_realvalue,%d", realvalue);
        report(clock(),workflow_event,str);
        //
        // [ INSTRUMENTACION: Task "filtering" finished. ]
        report(clock(),workflow_event,"task_finished,filtering");
        //
        // [ INSTRUMENTACION: Task "conversion" started. ]
        report(clock(),workflow_event,"task_started,conversion");
        //
        measurement(realvalue);
        bar(realvalue, realvalue_old);
        // [ INSTRUMENTACION: Task "conversion" finished. ]
        report(clock(),workflow_event,"task_finished,conversion");
        //
        realvalue_old = realvalue;
        // [ INSTRUMENTACION: Variable assigned. ]
        sprintf(str, "variable_value_assigned,main_realvalue_old,%d", realvalue_old);
        report(clock(),workflow_event,str);
        //
        // [ INSTRUMENTACION: Checkpoint filtering_chk alcanzado. ]
        report(clock(),workflow_event,"checkpoint_reached,display_chk");
        //
	} // WHILE
} // MAIN
