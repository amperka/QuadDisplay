// Подключаем библиотеку
#include <QuadDisplay.h>

// Допустим, индикатор подключен к 7-му пину
#define PIN 7

void setup()
{
}

void loop()
{
  // можно выводить целые числа
  displayInt(PIN, 123);
  delay(1000);

  // и отрицательные тоже
  displayInt(PIN, -123);
  delay(1000);

  // можно показывать ведущие нули (0012)
  displayInt(PIN, 12, true);
  delay(1000);

  // можно показывать вещественные числа
  // с заданной точностью, например 2 знака после запятой
  displayFloat(PIN, -1.23, 2);
  delay(1000);

  // можно показывать нехитрый текст (on/off, например) или
  // произвольную графику
  displayDigits(PIN, QD_O, QD_f, QD_f, QD_NONE); // off
  delay(1000);
  displayDigits(PIN, QD_O, QD_n, QD_NONE, QD_NONE); // on
  delay(1000);
  // и, конечно, всё очищать
  displayClear(PIN);
  delay(1000);
}
