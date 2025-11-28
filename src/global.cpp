#include "global.h"
float glob_temperature = 0;
float glob_humidity = 0;
float glob_tinyml_result = 0;

String WIFI_SSID;
String WIFI_PASS;
String CORE_IOT_TOKEN;
String CORE_IOT_SERVER;
String CORE_IOT_PORT;

String ssid = "ESP32-YOUR NETWORK HERE!!!";//not needed
String password = "12345678";
String wifi_ssid = "Thanh Binh";
String wifi_password = "thanhbinh2005#";//not needed
boolean isWifiConnected = false;
SemaphoreHandle_t xBinarySemaphoreInternet = xSemaphoreCreateBinary();
SemaphoreHandle_t xSemaphoreSensorAlert = xSemaphoreCreateBinary(); //alert semaphore
SemaphoreHandle_t xSensorDataMutex = xSemaphoreCreateMutex(); //synchronize sensor data access

// --- NEW QUEUE INITIALIZATION ---
// Create queues of size 1. We use size 1 because we only care about 
// the *most recent* value for blinking status.
QueueHandle_t xQueueTempLed = xQueueCreate(1, sizeof(float));
QueueHandle_t xQueueHumiNeo = xQueueCreate(1, sizeof(float));

boolean alert = false;