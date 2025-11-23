#include "global.h"

#include "led_blinky.h"
#include "neo_blinky.h"
#include "temp_humi_monitor.h"
// #include "mainserver.h"
#include "tinyml.h"
#include "coreiot.h"

// include task
#include "task_check_info.h"
#include "task_toogle_boot.h"
#include "task_wifi.h"
#include "task_webserver.h"
#include "task_core_iot.h"
#include "multi_task_task6.h"

void setup()
{
  Serial.begin(115200);
  check_info_File(0);
  //xTaskCreate(temp_humi_monitor, "Task TEMP HUMI Monitor", 2048, NULL, 2, NULL);
  // xTaskCreate(led_blinky, "Task LED Blink", 2048, NULL, 2, NULL);
  // xTaskCreate(neo_blinky, "Task NEO Blink", 2048, NULL, 2, NULL);
  // xTaskCreate(temp_humi_monitor, "Task TEMP HUMI Monitor", 2048, NULL, 2, NULL);
  // xTaskCreate(main_server_task, "Task Main Server" ,8192  ,NULL  ,2 , NULL);
  // xTaskCreate( tiny_ml_task, "Tiny ML Task" ,2048  ,NULL  ,2 , NULL);
  // xTaskCreate(coreiot_task, "CoreIOT Task" ,4096  ,NULL  ,2 , NULL);
  
  //192.168.4.1 connect here enter info then connect to home wifi and then enter the ip below
  //192.168.1.11 this is the main web
  
  //xTaskCreate(Task_Toogle_BOOT, "Task_Toogle_BOOT", 4096, NULL, 2, NULL);

  //--CHẠY TASK 6--
 //TaskCreate(Task1_OnBoardLed, "RGB Task", 2048, NULL, 1, NULL);
 //TaskCreate(Task2_VirtualLED, "Virtual", 2048, NULL, 1, NULL);
//TaskCreate(Task3_Button, "Button",  2048, NULL, 2, NULL);
}

void loop()
{
  vTaskDelete(NULL);
}