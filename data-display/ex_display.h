/*
 * This is a dummy implementation of a display
 * Its purpose is for the main application to compile and run.
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#include "rgb.h"

void display_rect(uint32_t HEIGHT, uint32_t WIDTH, uint32_t w, uint32_t h, const rgb* color);
void display_box(uint32_t HEIGHT, uint32_t WIDTH, uint32_t w, uint32_t h, const rgb* color);

void display_set_text_color(rgb color);
void display_set_text_bgcolor(rgb color);
void display_set_text_scale(uint8_t scale);
void display_set_text_pos(uint16_t HEIGHT, uint16_t WIDTH);
void display_set_text_pos2(uint16_t HEIGHT, uint16_t WIDTH);
void display_set_text_origin_position(uint16_t HEIGHT);
void display_write_text(const char* text);

void display_Show_RGB(unsigned char dat1,unsigned char dat2,unsigned char dat3, unsigned int HEIGHT0, unsigned int HEIGHT1, unsigned int WIDTH0, unsigned int WIDTH1);

#endif
