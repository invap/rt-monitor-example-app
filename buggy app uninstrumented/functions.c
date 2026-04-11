#include <math.h>
#include <stdio.h>

#include "functions.h"

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
                    printf("\n");
                }else{
                    // Pintar pixel de color 2 ( Bit = 1 )
                    display_set_pixel( ( hheightPosition - iLineCounter ) , ( wwidthPosition + iBitsCounter + (iWidthByteCounter * 8) ) , ccolor2 );
                    printf("\n");
                }
            }
        }
    }
}

void measurement(int16_t dato){
    float dato_ing = 0.00524590164*dato;
    float dato_ing2 = (1E-13 * pow(2.71828,(1.1231*dato_ing)));
    uint16_t pl =30; uint16_t ll =20;
    uint8_t scale =2;
    static char text_tmp[10];
    display_set_text_scale(scale);
    display_set_text_pos2( pl,  ll);
    display_set_text_color(color_g);
    display_set_text_bgcolor(color_black);
    if (dato_ing>20.98)
        sprintf(text_tmp, "**H    \n");
    else
        if (dato_ing < 3.5)
            sprintf(text_tmp, "**L    \n");
        else
            sprintf(text_tmp, "%2.0E  \n", dato_ing2);
    display_write_text(text_tmp);
    printf("\n");
}

void bar( int16_t dato, int16_t dato_old) {
    float dato_ing = 0.00524590164 * dato;
    float dato_ing_old = 0.00524590164 * dato_old;
    int g = (24 * dato_ing - 96);
    int h = (24 * dato_ing_old - 96);
    for (signed int i = 66; i < g + 66; i++) {
        if (i >= 49 & i < 178) {
            display_Show_RGB(0x00, 0xff, 0x00, (i), (i), 155, 190); //00ff00  1c542d
            printf("\n");
        }
        if (i >= 178 & i < 400) { //336
            display_Show_RGB(0xff, 0xff, 0x00, (i), (i), 155, 190);//FFFF00
            printf("\n");
        }
        if (i >= 400 & i < 450) {
            display_Show_RGB(0xff, 0x00, 0x00, (i), (i), 155, 190);
            printf("\n");
        }
    }
    if (g < h)
        for(signed int i = h+66 ; i > g+66 ; i--)
            if (i>=49 & i<450) {
                display_Show_RGB(0x00, 0x00, 0x00, ( i ), ( i ), 155 , 190 );
                printf("\n");
            }
}

void background(void) {
    uint16_t xl = 29;
    uint16_t yl = 1;
    uint8_t scale = 2;

    display_set_text_scale(scale);
    display_set_text_pos(xl, yl);
    display_set_text_origin_position(yl);
    display_set_text_color(color_white);
    display_write_text("         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n         \n");
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
    display_write_text("1E-11\n");
    display_set_text_pos2(x2, yl);
    display_write_text("1E-10\n");
    display_set_text_pos2(x3, yl);
    display_write_text(" 1E-9\n");
    display_set_text_pos2(x4, yl);
    display_write_text(" 1E-8\n");
    display_set_text_pos2(x5, yl);
    display_write_text(" 1E-7\n");
    display_set_text_pos2(x6, yl);
    display_write_text(" 1E-6\n");
    display_set_text_pos2(x7, yl);
    display_write_text(" 1E-5\n");
    display_set_text_pos2(x8, yl);
    display_write_text(" 1E-4\n");
    display_set_text_pos2(x9, yl);
    display_write_text(" 1E-3\n");
    display_box(0, 0, 479, 127, &color_blue);
    display_rect(0, 20, 1, 87, &color_black);
    display_rect(478, 20, 1, 87, &color_black);

    drawImage2Color_HSB8(27, 45, unidad, &color_black, &color_g);

    display_rect(50 + 14, 60, 2, 20, &color_white);
    display_rect(98 + 14, 60, 2, 20, &color_white);
    display_rect(146 + 14, 60, 2, 20, &color_white);
    display_rect(194 + 14, 60, 2, 20, &color_white);
    display_rect(242 + 14, 60, 2, 20, &color_white);
    display_rect(290 + 14, 60, 2, 20, &color_white);
    display_rect(338 + 14, 60, 2, 20, &color_white);
    display_rect(386 + 14, 60, 2, 20, &color_white);
    display_rect(434 + 14, 60, 2, 20, &color_white);
    printf("\n");
}
