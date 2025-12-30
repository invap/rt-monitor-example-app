#include <math.h>
#include <stdio.h>

#include "functions.h"

// Added to use the reporting API
#include "../../c-reporter-api/include/c-reporter-api.h"
#include "../../c-reporter-api/include/stopwatch.h"

// [ INSTRUMENTACION: Agregado para poder contabilizar el tiempo excluyendo el tiempo necesario para la instrumentación. ]
extern stopwatch reporting_clk;
//

rgb color_r = {0xFF,0x00, 0x00};
rgb color_y = {0xFF,0xFF, 0x00};
rgb color_g = {0x00,0xFF, 0x00};
rgb color_blue = {0x00,0x00, 0xFF};
rgb color_white = {0xFF,0xFF, 0xFF};
rgb color_black = {0x00,0x00, 0x00};

uint8_t const unidad[] = {
        0x00, 0x30, 0x00, 0x1C,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x06, 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0xC0,
        0x00, 0x00, 0x00, 0x00, 0x0C, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x40, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00,
        0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x30, 0x18,
        0x00, 0x00, 0x00, 0x00, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0x60, 0x0C, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void drawImage2Color_HSB8( uint16_t hheightPosition , uint16_t wwidthPosition , uint8_t const * bbitMapMatrix , const rgb * ccolor1 ,  const rgb* ccolor2 ){
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    uint16_t widthBitMapMatrix_8 , heigthBitMapMatrix;
    uint8_t bitMapTemp;

    // Extraer de la matriz el tama�o de la imagen
    widthBitMapMatrix_8  = ( ( ( ( (uint16_t)(bbitMapMatrix[ 0 ]) ) << 8 ) & 0xFF00 ) | ( ((uint16_t)(bbitMapMatrix[ 1 ])) & 0x00FF ) ) / ( (uint16_t)(8) );
    heigthBitMapMatrix   = ( ( (   (uint16_t)(bbitMapMatrix[ 2 ]) ) << 8 ) & 0xFF00 ) | ( ((uint16_t)(bbitMapMatrix[ 3 ])) & 0x00FF );

    // Recorrer linea (Heigth)
    for( uint8_t iLineCounter = 0 ; iLineCounter < heigthBitMapMatrix ; iLineCounter++ ){
        // Recorrer ancho formado por bytes ( Width / 8 )
        for( uint8_t iWidthByteCounter = 0 ; iWidthByteCounter < widthBitMapMatrix_8 ; iWidthByteCounter++ ){
            // --- Recorrer Byte ---
            for( uint8_t iBitsCounter = 0 ; iBitsCounter < 8 ; iBitsCounter++ ){
                // Calcular posici�n del bit
                bitMapTemp = ( bbitMapMatrix[ 4 + iWidthByteCounter + ( widthBitMapMatrix_8 * iLineCounter ) ] << iBitsCounter ) & ( 0x80 );
                // Verifiacr valor del bit para pintar su pixel correspondiente
                if( bitMapTemp == 0 ){
                    // Pintar pixel de color 1 ( Bit = 0 )
                    display_set_pixel( ( hheightPosition - iLineCounter ) , ( wwidthPosition + iBitsCounter + (iWidthByteCounter * 8) ) , ccolor1 );
                    // [ INSTRUMENTACION: component event. ]
                    sprintf(str, "display,display_set_pixel,%u,%u,%u,%u,%u",( hheightPosition - iLineCounter ), ( wwidthPosition + iBitsCounter + (iWidthByteCounter * 8) ), (*ccolor1).r, (*ccolor1).g, (*ccolor1).b);
                    report(component_event,str);
                    //
                }else{
                    // Pintar pixel de color 2 ( Bit = 1 )
                    display_set_pixel( ( hheightPosition - iLineCounter ) , ( wwidthPosition + iBitsCounter + (iWidthByteCounter * 8) ) , ccolor2 );
                    // [ INSTRUMENTACION: component event. ]
                    sprintf(str, "display,display_set_pixel,%u,%u,%u,%u,%u",( hheightPosition - iLineCounter ), ( wwidthPosition + iBitsCounter + (iWidthByteCounter * 8) ), (*ccolor2).r, (*ccolor2).g, (*ccolor2).b);
                    report(component_event,str);
                    //
                }
            }
        }
    }
}

void measurement(int16_t dato){
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    float dato_ing = 0.00524590164*dato;
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&reporting_clk);
    sprintf(str, "variable_value_assigned,measurement_dato_ing,%.7f",dato_ing);
    report(state_event,str);
    resume(&reporting_clk);
    //
    float dato_ing2 = (1E-13 * pow(2.71828,(1.1231*dato_ing)));
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&reporting_clk);
    sprintf(str, "variable_value_assigned,measurement_dato_ing2,%.7f",dato_ing2);
    report(state_event,str);
    resume(&reporting_clk);
    //
    uint16_t pl =30; uint16_t ll =20;
    uint8_t scale =2;
    static char text_tmp[10];
    display_set_text_scale(scale);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_scale,%u",scale);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2( pl,  ll);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u",pl,ll);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_color(color_g);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_color,%u,%u,%u", color_g.r, color_g.g, color_g.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_bgcolor(color_black);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_bgcolor,%u,%u,%u", color_black.r, color_black.g, color_black.b);
    report(component_event,str);
    resume(&reporting_clk);
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
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text,%s", text_tmp);
    report(component_event,str);
    resume(&reporting_clk);
    //
}

void bar( int16_t dato, int16_t dato_old) {
    // [ INSTRUMENTACION: Agregado para poder enviar el string especificando el evento. ]
    char str[MAX_EVENT_SIZE];
    //
    float dato_ing = 0.00524590164 * dato;
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&reporting_clk);
    sprintf(str, "variable_value_assigned,bar_dato_ing,%.7f",dato_ing);
    report(state_event,str);
    resume(&reporting_clk);
    //
    float dato_ing_old = 0.00524590164 * dato_old;
    /* Sentencias incorrectas: Error de representación de las muestras:
     *      dato > 3812 implies g > 383
     *      dato < 755 implies g < 0
     * int g = (24 * dato_ing - 96);
     * int h = (24 * dato_ing_old - 96);
     */
    int g = ((24 * dato_ing - 96) <= 0) ? 0 : ((24 * dato_ing - 96) >= 383) ? 383 : (24 * dato_ing - 96);
    int h = ((24 * dato_ing_old - 96) <= 0) ? 0 : ((24 * dato_ing_old - 96) >= 383) ? 383 : (24 * dato_ing_old - 96);
    // [ INSTRUMENTACION: Variable assigned. ]
    pause(&reporting_clk);
    sprintf(str, "variable_value_assigned,bar_point,%d",g);
    report(state_event,str);
    resume(&reporting_clk);
    //
    for (signed int i = 66; i < g + 66; i++) {
        if (i >= 49 & i < 178) {
            display_Show_RGB(0x00, 0xff, 0x00, (i), (i), 155, 190); //00ff00  1c542d
            // [ INSTRUMENTACION: component event. ]
            pause(&reporting_clk);
            sprintf(str, "display,display_Show_RGB,%u,%u,%u,%u,%u,%u,%u", 0, 255, 0, (i), (i), 155, 190);
            report(component_event,str);
            resume(&reporting_clk);
            //
        }
        if (i >= 178 & i < 400) { //336
            display_Show_RGB(0xff, 0xff, 0x00, (i), (i), 155, 190);//FFFF00
            // [ INSTRUMENTACION: component event. ]
            pause(&reporting_clk);
            sprintf(str, "display,display_Show_RGB,%u,%u,%u,%u,%u,%u,%u", 0, 255, 0, (i), (i), 155, 190);
            report(component_event,str);
            resume(&reporting_clk);
            //
        }
        if (i >= 400 & i < 450) {
            display_Show_RGB(0xff, 0x00, 0x00, (i), (i), 155, 190);
            // [ INSTRUMENTACION: component event. ]
            pause(&reporting_clk);
            sprintf(str, "display,display_Show_RGB,%u,%u,%u,%u,%u,%u,%u", 0, 255, 0, (i), (i), 155, 190);
            report(component_event,str);
            resume(&reporting_clk);
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
                pause(&reporting_clk);
                sprintf(str, "display,display_Show_RGB,%u,%u,%u,%u,%u,%u,%u", 0, 0, 0, (i), (i), 155, 190);
                report(component_event,str);
                resume(&reporting_clk);
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
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_scale,%u", scale);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos(xl, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos,%u,%u", xl, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_origin_position(yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_origin_position,%u", yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_color(color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_color,%u,%u,%u", color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
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
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text,         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n");
    report(component_event,str);
    resume(&reporting_clk);
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
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x0, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text("1E-11\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text,1E-11\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2(x2, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x2, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text("1E-10\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text,1E-10\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2(x3, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x3, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text(" 1E-9\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text, 1E-9\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2(x4, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x4, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text(" 1E-8\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text, 1E-8\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2(x5, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x5, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text(" 1E-7\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text, 1E-7\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2(x6, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x6, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text(" 1E-6\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text, 1E-6\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2(x7, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x7, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text(" 1E-5\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text, 1E-5\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2(x8, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x8, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text(" 1E-4\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text, 1E-4\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_set_text_pos2(x9, yl);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_set_text_pos2,%u,%u", x9, yl);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_write_text(" 1E-3\n");
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_write_text, 1E-3\n");
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_box(0, 0, 479, 127, &color_blue);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_box,%u,%u,%u,%u,%u,%u,%u", 0, 0, 479, 127, color_blue.r, color_blue.g, color_blue.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(0, 20, 1, 87, &color_black);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 0, 20, 1, 87, color_black.r, color_black.g, color_black.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(478, 20, 1, 87, &color_black);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 478, 20, 1, 87, color_black.r, color_black.g, color_black.b);
    report(component_event,str);
    resume(&reporting_clk);
    //

    drawImage2Color_HSB8(27, 45, unidad, &color_black, &color_g);

    display_rect(50 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 50+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(98 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 98+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(146 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 146+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(194 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 194+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(242 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 242+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(290 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 290+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(338 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 338+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(386 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 386+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
    display_rect(434 + 14, 60, 2, 20, &color_white);
    // [ INSTRUMENTACION: component event. ]
    pause(&reporting_clk);
    sprintf(str, "display,display_rect,%u,%u,%u,%u,%u,%u,%u", 434+14, 60, 2, 20, color_white.r, color_white.g, color_white.b);
    report(component_event,str);
    resume(&reporting_clk);
    //
}
