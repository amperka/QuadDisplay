
#include <Arduino.h>

#include "QuadDisplay.h"

const static uint8_t numerals[] = {QD_0, QD_1, QD_2, QD_3, QD_4, QD_5, QD_6, QD_7, QD_8, QD_9};

static void sendByte(uint8_t pin, byte data, byte n = 8)
{
    for (byte i = n; i > 0; i--) {
        if (data & 1) {
            noInterrupts();
            digitalWrite(pin, LOW);
            digitalWrite(pin, HIGH);
            interrupts();
            delayMicroseconds(30);
        }
        else {
            digitalWrite(pin, LOW);
            delayMicroseconds(15);
            digitalWrite(pin, HIGH);
            delayMicroseconds(60);
        }
        data >>= 1;
    }
}

static void latch(uint8_t pin)
{
    digitalWrite(pin, LOW);
    delayMicroseconds(100);
    digitalWrite(pin, HIGH);
    delayMicroseconds(300);
}

void displayDigits(uint8_t pin, uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    sendByte(pin, digit1);
    sendByte(pin, digit2);
    sendByte(pin, digit3);
    sendByte(pin, digit4);
    latch(pin);
}

void displayClear(uint8_t pin)
{
    displayDigits(pin, QD_NONE, QD_NONE, QD_NONE, QD_NONE);
}


void displayInt(uint8_t pin, int val, bool padZeros, uint8_t dots)
{
    bool negative = val < 0;
    val = abs(val);
    uint8_t digits[4] = {0xff, 0xff, 0xff, 0xff};

    int8_t i;
    for (i = 4; i--; ) {
        uint8_t digit = val % 10;
        digits[i] = (val || padZeros) ? numerals[digit] : 0xff;

        val /= 10;
        if (!val && !padZeros)
            break;
    }

    if (negative)
        digits[max(0, i-1)] = QD_MINUS;

    for (i = 4; i--; ) {
        if (dots & (1 << i))
            digits[4 - i] &= QD_DOT;
    }

    displayDigits(pin, digits[0], digits[1], digits[2], digits[3]);
}

void displayFloat(uint8_t pin, float val, uint8_t precision, bool padZeros)
{
    uint8_t dot = 0x1;
    while (precision) {
        val *= 10;
        --precision;
        dot <<= 1;
    }

    displayInt(pin, (int)val, padZeros, dot);
}
