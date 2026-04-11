#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../data-source/ex_adc.h"
#include "functions.h"

int main( void ){
    uint16_t realvalue_old, value, addition, realvalue;
    adc_init ();
    background();
    // [ POTENTIAL PROBLEM FOUND: realvalue_old was not initialized.  ]
    realvalue_old = 0;
    printf("\n");
    while (1) {
        addition = 0;
        printf("\n");
        for (int16_t i=0;i<16; i++){
            value = sample ();
            addition = addition + value;
            printf("\n");
        }
        realvalue = addition/16;
        measurement(realvalue);
        bar(realvalue, realvalue_old);
        realvalue_old = realvalue;
        printf("\n");
	} // WHILE
} // MAIN
