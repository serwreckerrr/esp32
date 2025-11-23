#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>

void TaskBlinkOnboard(void *pvParameters);
void TaskVirtualLED(void *pvParameters);
void TaskButton(void *pvParameters);
