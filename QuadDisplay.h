/*
 * Copyright (c) 2014 by Amperka LLC
 * QuadDisplay Driver Library
 * Authors:
 *   - Victor Nakoryakov <victor at amperka.ru>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef QUAD_DISPLAY
#define QUAD_DISPLAY

#include <inttypes.h> 

/*

    ___7___
   /       \
  |         |
 2|         |6
   \___1___/
   /       \
  |         |
 3|         |5
   \___4___/
               *0
 */

#define QD_NONE  0b11111111
#define QD_DOT   0b11111110
#define QD_MINUS 0b11111101

#define QD_UNDERSCORE 0b11101111
#define QD_DEGREE     0b00111001

#define QD_0 0b00000011
#define QD_1 0b10011111
#define QD_2 0b00100101
#define QD_3 0b00001101
#define QD_4 0b10011001
#define QD_5 0b01001001
#define QD_6 0b01000001
#define QD_7 0b00011111
#define QD_8 0b00000001
#define QD_9 0b00001001

#define QD_A 0b00010001
#define QD_a 0b00000101
#define QD_b 0b11000001
#define QD_C 0b01100011
#define QD_c 0b11100101
#define QD_d 0b10000101
#define QD_E 0b01100001
#define QD_f 0b01110001
#define QD_F QD_f
#define QD_H 0b10010001
#define QD_h 0b11010001
#define QD_I QD_1
#define QD_J 0b10001111
#define QD_L 0b11100011
#define QD_n 0b11010101
#define QD_o 0b11000101
#define QD_O QD_0
#define QD_P 0b00110001
#define QD_r 0b11110101
#define QD_S 0b01001001
#define QD_t 0b11100001
#define QD_u 0b11000111
#define QD_U 0b10000011
#define QD_Y 0b10001001


void displayInt(uint8_t pin, int val, bool padZeros=false, uint8_t dots=0x00);
void displayFloat(uint8_t pin, float val, uint8_t precision, bool padZeros=false);
void displayDigits(uint8_t pin, uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4);
void displayClear(uint8_t pin);

void displayTemperatureC(uint8_t pin, int val, bool padZeros=false);

#endif
