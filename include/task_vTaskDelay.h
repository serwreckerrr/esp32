#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

void Task1_OnBoardLed(void *pvParameters);
void Task2_VirtualLED(void *pvParameters);
void Task3_Button(void *pvParameters);
