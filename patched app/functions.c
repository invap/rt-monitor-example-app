#include <math.h>
#include <stdio.h>

#include "functions.h"

// Added to use the reporting API
#include "../../c-reporter-api/src/c-reporter-api.h"

// [ INSTRUMENTACION: Agregado para poder contabilizar el tiempo excluyendo el tiempo necesario para la instrumentación. ]
extern timer clk;
//

rgb color_r = {0xFF,0x00, 0x00};
rgb color_y = {0xFF,0xFF, 0x00};
rgb color_g = {0x00,0xFF, 0x00};
rgb color_blue = {0x00,0x00, 0xFF};
rgb color_white = {0xFF,0xFF, 0xFF};
rgb color_black = {0x00,0x00, 0x00};

void measurement(int16_t dato){
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    float dato_ing = 0.00524590164*dato;
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&clk);
    sprintf(str, "variable_value_assigned,measurement_dato_ing,%.7f",dato_ing);
    report(workflow_event,str);
    resume(&clk);
    //
    float dato_ing2 = (1E-13 * pow(2.71828,(1.1231*dato_ing)));
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&clk);
    sprintf(str, "variable_value_assigned,measurement_dato_ing2,%.7f",dato_ing2);
    report(workflow_event,str);
    resume(&clk);
    //
    uint16_t pl =30; uint16_t ll =20;
    uint8_t scale =2;
    static char text_tmp[10];
    display_set_text_scale(scale);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_scale,%u",scale);
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2( pl,  ll);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u",pl,ll);
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_color(color_g);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_color,%u,%u,%u", color_g.r, color_g.g, color_g.b);
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_bgcolor(color_black);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_bgcolor,%u,%u,%u", color_black.r, color_black.g, color_black.b);
    report(component_event,str);
    resume(&clk);
    //
    if (dato_ing>20.98)
        sprintf(text_tmp, "**H    \n");
    else
       if (dato_ing<3.5)
           sprintf(text_tmp, "**L    \n");
       else
           sprintf(text_tmp, "%2.0E \n", dato_ing2);
    display_write_text(text_tmp);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text,%s", text_tmp);
    report(component_event,str);
    resume(&clk);
    //
}

void bar( int16_t dato, int16_t dato_old) {
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    float dato_ing = 0.00524590164 * dato;
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&clk);
    sprintf(str, "variable_value_assigned,bar_dato_ing,%.7f",dato_ing);
    report(workflow_event,str);
    resume(&clk);
    //
    float dato_ing_old = 0.00524590164 * dato_old;

    /* Sentencia incorrecta: Error de subrepresentación de las muestras grandes
     * int point = (24 * dato_ing - 96);
     */
    int point = ((24 * dato_ing - 96) >= 383) ? 383 : (24 * dato_ing - 96);

    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&clk);
    sprintf(str, "variable_value_assigned,bar_point,%d",point);
    report(workflow_event,str);
    resume(&clk);
    //

    /* Sentencias incorrectas: Error de subrepresentación de las muestras grandes
     * int g = (24 * dato_ing - 96);
     * int h = (24 * dato_ing_old - 96);
     */
    int g = ((24 * dato_ing - 96) >= 383) ? 383 : (24 * dato_ing - 96);
    int h = ((24 * dato_ing_old - 96) >= 383) ? 383 : (24 * dato_ing_old - 96);

    for (signed int i = 66; i < g + 66; i++) {
        if (i >= 49 & i < 178) {
            display_Show_RGB(0x00, 0xff, 0x00, (i), (i), 155, 190); //00ff00  1c542d
            // [ INSTRUMENTACION: component event. ]
            pause(&clk);
            sprintf(str, "display,display_Show_RGB,%u,%u,%u,%u,%u,%u,%u", 0, 255, 0, (i), (i), 155, 190);
            report(component_event,str);
            resume(&clk);
            //
        }
        if (i >= 178 & i < 400) { //336
            display_Show_RGB(0xff, 0xff, 0x00, (i), (i), 155, 190);//FFFF00
            // [ INSTRUMENTACION: component event. ]
            pause(&clk);
            sprintf(str, "display,display_Show_RGB,%u,%u,%u,%u,%u,%u,%u", 0, 255, 0, (i), (i), 155, 190);
            report(component_event,str);
            resume(&clk);
            //
        }
        if (i >= 400 & i < 450) {
            display_Show_RGB(0xff, 0x00, 0x00, (i), (i), 155, 190);
            // [ INSTRUMENTACION: component event. ]
            pause(&clk);
            sprintf(str, "display,display_Show_RGB,%u,%u,%u,%u,%u,%u,%u", 0, 255, 0, (i), (i), 155, 190);
            report(component_event,str);
            resume(&clk);
            //
        }
    }
    if (g < h)
        /* Sentencia incorrecta: Error de despintado de una fila de la barra
         * for(signed int i = h+66 ; i > g+66 ; i--)
         */
        for(signed int i = h+66-1 ; i >= g+66 ; i--)
            if (i>=49 & i<450) {
                display_Show_RGB(0x00, 0x00, 0x00, ( i ), ( i ), 155 , 190 );
                // [ INSTRUMENTACION: component event. ]
                pause(&clk);
                sprintf(str, "display,display_Show_RGB,%u,%u,%u,%u,%u,%u,%u", 0, 0, 0, (i), (i), 155, 190);
                report(component_event,str);
                resume(&clk);
                //
            }
}

void background(void) {
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    uint16_t xl = 29;
    uint16_t yl = 1;
    uint8_t scale = 2;

    display_set_text_scale(scale);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_scale,%u", scale);
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos(xl, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos,%u,%u", xl, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_origin_position(yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_origin_position,%u", yl);
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_color(color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_color,%u,%u,%u", color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //

    display_write_text(
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
            "         \n"
    );
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text,         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n");
    report(component_event,str);
    resume(&clk);
    //
    uint16_t x0 = 60;
    yl = 0;
    uint16_t x2 = 108;
    uint16_t x3 = 156;
    uint16_t x4 = 204;
    uint16_t x5 = 252;
    uint16_t x6 = 300;
    uint16_t x7 = 348;
    uint16_t x8 = 396;
    uint16_t x9 = 444;
    display_set_text_pos2(x0, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x0, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text("1E-11\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text,1E-11\n");
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2(x2, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x2, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text("1E-10\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text,1E-10\n");
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2(x3, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x3, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text(" 1E-9\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text, 1E-9\n");
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2(x4, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x4, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text(" 1E-8\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text, 1E-8\n");
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2(x5, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x5, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text(" 1E-7\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text, 1E-7\n");
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2(x6, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x6, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text(" 1E-6\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text, 1E-6\n");
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2(x7, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x7, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text(" 1E-5\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text, 1E-5\n");
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2(x8, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x8, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text(" 1E-4\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text, 1E-4\n");
    report(component_event,str);
    resume(&clk);
    //
    display_set_text_pos2(x9, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x9, yl);
    report(component_event,str);
    resume(&clk);
    //
    display_write_text(" 1E-3\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_write_text, 1E-3\n");
    report(component_event,str);
    resume(&clk);
    //
    display_box(0, 0, 479, 127, &color_blue);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_box,%u,%u,%u,%u,%u,%u,%u", 0, 0, 479, 127, color_blue.r, color_blue.g, color_blue.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(0, 20, 1, 87, &color_black);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 0, 20, 1, 87, color_black.r, color_black.g, color_black.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(478, 20, 1, 87, &color_black);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 478, 20, 1, 87, color_black.r, color_black.g, color_black.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(50 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 50+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(98 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 98+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(146 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 146+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(194 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 194+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(242 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 242+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(290 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 290+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(338 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 338+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(386 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 386+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
    display_rect(434 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 434+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&clk);
    //
}
