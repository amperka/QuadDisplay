
#include <Arduino.h>

#include "QuadDisplay.h"

#include "pins_arduino.h"


#ifndef _VARIANT_ARDUINO_DUE_X_

#define MACRO_DIGITAL_WRITE(a,b) (fastDigitalWrite(a,b))

    //Fast version of digitalWrite, without using turnOffPWM
    //
void fastDigitalWrite(uint8_t pin, uint8_t val)
{
      //uint8_t timer = digitalPinToTimer(pin);
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *out;

    if (port == NOT_A_PIN) return;

    // If the pin that support PWM output, we need to turn it off
    // before doing a digital write.
    // DELETED. Timer is already off here . Amperka
    // if (timer != NOT_ON_TIMER) turnOffPWM(timer);

    out = portOutputRegister(port);

    uint8_t oldSREG = SREG;
    cli();

    if (val == LOW) {
        *out &= ~bit;
    } else {
        *out |= bit;
    }

    SREG = oldSREG;
}


#else

#define MACRO_DIGITAL_WRITE(a,b) (digitalWrite(a,b))

#endif

const static uint8_t numerals[] = {QD_0, QD_1, QD_2, QD_3, QD_4, QD_5, QD_6, QD_7, QD_8, QD_9};

static void sendByte(uint8_t pin, byte data, byte n = 8)
{
    for (byte i = n; i > 0; i--) {
        if (data & 1) {
            noInterrupts();
            MACRO_DIGITAL_WRITE(pin, LOW);
            MACRO_DIGITAL_WRITE(pin, HIGH);
            interrupts();
            delayMicroseconds(30);
        }
        else {
            MACRO_DIGITAL_WRITE(pin, LOW);
            delayMicroseconds(15);
            MACRO_DIGITAL_WRITE(pin, HIGH);
            delayMicroseconds(60);
        }
        data >>= 1;
    }
}

static void latch(uint8_t pin)
{
    MACRO_DIGITAL_WRITE(pin, LOW);
    delayMicroseconds(100);
    MACRO_DIGITAL_WRITE(pin, HIGH);
    delayMicroseconds(300);
}

void displayDigits(uint8_t pin, uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4)
{
    pinMode(pin, OUTPUT);
    //turnOffPWM work here:
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
    uint8_t digits[4] = {0xff, 0xff, 0xff, 0xff};

    if (!padZeros && !val)
        digits[3] = numerals[0];
    else {
        bool negative = val < 0;
        val = abs(val);


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

void displayTemperatureC(uint8_t pin, int val, bool padZeros)
{

    uint8_t digits[4] = {0xff, 0xff, QD_DEGREE, QD_C};
    
    if (!padZeros && !val)
        digits[1] = numerals[0];
    else {
        bool negative = val < 0;
        val = abs(val);

        int8_t i;
        for (i = 2; i--; ) {
            uint8_t digit = val % 10;
            digits[i] = (val || padZeros) ? numerals[digit] : 0xff;

            val /= 10;
            if (!val && !padZeros)
                break;
        }

        if (negative)
            digits[max(0, i-1)] = QD_MINUS;
    }
    displayDigits(pin, digits[0], digits[1], digits[2], digits[3]);
}