// Подключаем библиотеку
#include <QuadDisplay.h>

// номер цифрового пина дисплея
#define DISPLAY_PIN 9

void setup()
{
}

void loop()
{
  // можно выводить целые числа
  displayInt(DISPLAY_PIN, 123);
  delay(1000);

  // и отрицательные тоже
  displayInt(DISPLAY_PIN, -123);
  delay(1000);

  // можно показывать ведущие нули (0012)
  displayInt(DISPLAY_PIN, 12, true);
  delay(1000);

  // можно показывать вещественные числа
  // с заданной точностью, например 2 знака после запятой
  displayFloat(DISPLAY_PIN, -1.23, 2);
  delay(1000);
  
  // можно показывать температуру в °C
  displayTemperatureC(DISPLAY_PIN, -5);
  delay(1000);
  
  // можно показывать нехитрый текст (on/off, например) или
  // произвольную графику
  displayDigits(DISPLAY_PIN, QD_O, QD_f, QD_f, QD_NONE); // off
  delay(1000);
  displayDigits(DISPLAY_PIN, QD_O, QD_n, QD_NONE, QD_NONE); // on
  delay(1000);
  // и, конечно, всё очищать
  displayClear(DISPLAY_PIN);
  delay(1000);
}
