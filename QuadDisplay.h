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

#define QD_NONE  0b11111111
#define QD_DOT   0b11111110
#define QD_MINUS 0b11111101

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

void displayInt(uint8_t pin, int val, bool padZeros=false, uint8_t dots=0x00);
void displayFloat(uint8_t pin, float val, uint8_t precision, bool padZeros=false);
void displayDigits(uint8_t pin, uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4);
void displayClear(uint8_t pin);


#endif
