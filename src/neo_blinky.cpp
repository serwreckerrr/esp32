#include "neo_blinky.h"
#include "global.h"

void neo_blinky(void *pvParameters){

    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    float local_humi = 0.0;

    while(1) {       
        // Safely read the global variable into a local one
        if (xSemaphoreTake(xSensorDataMutex, (TickType_t)10) == pdTRUE) {
            local_humi = glob_humidity;
            xSemaphoreGive(xSensorDataMutex);
        }
        if(xSemaphoreTake(xSemaphoreSensorAlert, 0) == pdTRUE){
            alert = !alert;
        }
        if(alert){
            strip.setPixelColor(0, strip.Color(255, 255, 0)); // Màu Vàng
            strip.show();
        }
        else{
            strip.clear();
            strip.show();
        }
        vTaskDelay(500);
        // if(glob_humidity < 70){
        //     strip.setPixelColor(0, strip.Color(0, 255, 0)); // Set pixel 0 to red
        //     strip.show(); // Update the strip

        //     // Wait for 500 milliseconds
        //     vTaskDelay(500);

        //     // Set the pixel to off
        //     strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
        //     strip.show(); // Update the strip

        //     // Wait for another 500 milliseconds
        //     vTaskDelay(500);
        // }   
        // else if(glob_humidity < 80 && glob_humidity >= 70){
        //     strip.setPixelColor(0, strip.Color(0, 0, 255)); // Set pixel 0 to red
        //     strip.show(); // Update the strip

        //     // Wait for 500 milliseconds
        //     vTaskDelay(500);

        //     // Set the pixel to off
        //     strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
        //     strip.show(); // Update the strip

        //     // Wait for another 500 milliseconds
        //     vTaskDelay(500);
        // }
        // else{
        //     strip.setPixelColor(0, strip.Color(255, 0, 0)); // Set pixel 0 to red
        //     strip.show(); // Update the strip

        //     // Wait for 500 milliseconds
        //     vTaskDelay(500);

        //     // Set the pixel to off
        //     strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn pixel 0 off
        //     strip.show(); // Update the strip

        //     // Wait for another 500 milliseconds
        //     vTaskDelay(500);
        // }                
        
    }
}