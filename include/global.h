#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <freertos/queue.h> // Include Queue support

extern float glob_temperature;
extern float glob_humidity;
extern float glob_tinyml_result;

extern String WIFI_SSID;
extern String WIFI_PASS;
extern String CORE_IOT_TOKEN;
extern String CORE_IOT_SERVER;
extern String CORE_IOT_PORT;

extern boolean isWifiConnected;
extern SemaphoreHandle_t xBinarySemaphoreInternet;
extern SemaphoreHandle_t xSemaphoreSensorAlert; //to signal alert
extern SemaphoreHandle_t xSensorDataMutex; // <-- ADDED THIS LINE for task 1 and 2 to safely access global sensor data

extern QueueHandle_t xQueueTempLed; // Queue for sending Temp to LED Task
extern QueueHandle_t xQueueHumiNeo; // Queue for sending Humi to NeoPixel Task

extern boolean alert;//to indicate alert status
#endif