#include "led_blinky.h"

void led_blinky(void *pvParameters){
    pinMode(LED_GPIO, OUTPUT);
    float local_temp = 0.0; // Local copy of temperature
    float received_temp = 0.0; // Temp variable for queue reception
  
  while(1) {           
    // --- QUEUE RECEIVE (New Logic) ---
    // Check if there is a new temperature value in the queue.
    // We use wait time '0' (non-blocking). If no new data, we continue using old local_temp.
    if (xQueueReceive(xQueueTempLed, &received_temp, 0) == pdTRUE) {
        local_temp = received_temp;
    }

    //normal blink
    if(glob_temperature < 27){
      digitalWrite(LED_GPIO, HIGH);  // turn the LED ON
      vTaskDelay(1000);
      digitalWrite(LED_GPIO, LOW);  // turn the LED OFF
      vTaskDelay(1000);
    }

    //medium blink
    else if(glob_temperature >= 27 && glob_temperature <32){
      digitalWrite(LED_GPIO, HIGH);  // turn the LED ON
      vTaskDelay(250);
      digitalWrite(LED_GPIO, LOW);  // turn the LED OFF
      vTaskDelay(250);
    }

    //fast/warning blink
    else {
      digitalWrite(LED_GPIO, HIGH);  // turn the LED ON
      vTaskDelay(50);
      digitalWrite(LED_GPIO, LOW);  // turn the LED OFF
      vTaskDelay(50);
    }           
  }
}