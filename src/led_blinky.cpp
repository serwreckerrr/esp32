#include "led_blinky.h"

void led_blinky(void *pvParameters){
    pinMode(LED_GPIO, OUTPUT);
    float local_temp = 0.0; // Local copy of temperature
  
  while(1) {           
    // if(glob_humidity >= 80.0f){
    //   digitalWrite(LED_GPIO, HIGH);  // turn the LED ON
    //   vTaskDelay(1000);
    //   digitalWrite(LED_GPIO, LOW);  // turn the LED OFF
    //   vTaskDelay(1000);
    // }

    
    // Safely read the global variable into a local one
    if (xSemaphoreTake(xSensorDataMutex, (TickType_t)10) == pdTRUE) {
        local_temp = glob_temperature;
        xSemaphoreGive(xSensorDataMutex);
    }

    if(glob_temperature < 27){
      digitalWrite(LED_GPIO, HIGH);  // turn the LED ON
      vTaskDelay(1000);
      digitalWrite(LED_GPIO, LOW);  // turn the LED OFF
      vTaskDelay(1000);
    }
    else if(glob_temperature >= 27 && glob_temperature <32){
      digitalWrite(LED_GPIO, HIGH);  // turn the LED ON
      vTaskDelay(250);
      digitalWrite(LED_GPIO, LOW);  // turn the LED OFF
      vTaskDelay(250);
    }
    else {
      digitalWrite(LED_GPIO, HIGH);  // turn the LED ON
      vTaskDelay(50);
      digitalWrite(LED_GPIO, LOW);  // turn the LED OFF
      vTaskDelay(50);
    }           
  }
}