#include <QuadDisplay.h>
//Отображаем количество секунд, прошедшее со старта скетча
#define DISPLAY_PIN 12

void setup() {
}

void loop() {
  float currentTime = (float)millis() / 1000;
  
  displayFloat(DISPLAY_PIN, currentTime, 1);
  
  delay(50);
}
