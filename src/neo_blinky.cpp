#include "neo_blinky.h"
#include "global.h"

void neo_blinky(void *pvParameters){

    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    float local_humi = 0.0;
    float received_humi = 0.0;

    while(1) {  
        // --- QUEUE RECEIVE (New Logic) ---
        // Check if there is a new humidity value in the queue.
        // We use wait time '0' so the animation isn't blocked by waiting for data.     
        if (xQueueReceive(xQueueHumiNeo, &received_humi, 0) == pdTRUE) {
            local_humi = received_humi;
        }

        //toggle alert status
        if(xSemaphoreTake(xSemaphoreSensorAlert, 0) == pdTRUE){
            alert = !alert;
        }
        //alerted status
        if(alert){
            strip.setPixelColor(0, strip.Color(255, 255, 0)); // set to yellow if critical alert
            strip.show();
        }
        else{//normal monitoring
            if(glob_humidity < 70){
                strip.setPixelColor(0, strip.Color(0, 255, 0)); // Set pixel to green
                strip.show(); // Update the strip

                // Wait for 500 milliseconds
                vTaskDelay(500);

                // Set the pixel to off
                strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
                strip.show(); // Update the strip

                // Wait for another 500 milliseconds
                vTaskDelay(500);
            }   
            else if(glob_humidity < 80 && glob_humidity >= 70){
                strip.setPixelColor(0, strip.Color(0, 0, 255)); // Set pixel 0 to blue
                strip.show(); // Update the strip

                // Wait for 500 milliseconds
                vTaskDelay(500);

                // Set the pixel to off
                strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
                strip.show(); // Update the strip

                // Wait for another 500 milliseconds
                vTaskDelay(500);
            }
            else{
                strip.setPixelColor(0, strip.Color(255, 0, 0)); // Set pixel 0 to red
                strip.show(); // Update the strip

                // Wait for 500 milliseconds
                vTaskDelay(500);

                // Set the pixel to off
                strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
                strip.show(); // Update the strip

                // Wait for another 500 milliseconds
                vTaskDelay(500);
            }  
        }
        vTaskDelay(500);                   
    }
}