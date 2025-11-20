#include "global.h"
float glob_temperature = 0;
float glob_humidity = 0;

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
SemaphoreHandle_t xSemaphoreSensorAlert = xSemaphoreCreateBinary(); // <-- ADDED THIS LINE
SemaphoreHandle_t xSensorDataMutex = xSemaphoreCreateMutex(); // <-- ADDED THIS LINE for task 1 and 2
boolean alert = false;