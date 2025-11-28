#include "temp_humi_monitor.h"

// --- Define Sensor Thresholds ---
#define TEMP_CRITICAL 30.0
#define TEMP_WARNING 28.0

// --- Sensor and Display Objects ---
DHT20 dht20;
// Initialize LCD with I2C address 33 (0x21), 16 columns, 2 rows
LiquidCrystal_I2C lcd(33, 16, 2); 

//local alert to make sure semaphore given only once
boolean local_alert = false;

void temp_humi_monitor(void *pvParameters) {

    // --- One-Time Setup ---
    Wire.begin(11, 12);     // Initialize I2C bus (SDA, SCL)
    Serial.begin(115200);   // Initialize Serial for debugging
    
    dht20.begin();          // Initialize DHT20 sensor
    
    lcd.begin();            // Initialize the LCD
    lcd.backlight();        // Turn on the backlight
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Init...");
    vTaskDelay(1000); // Show init message

    // --- Task Loop ---
    while (1) {
        
        dht20.read();
        float temperature = dht20.getTemperature();
        float humidity = dht20.getHumidity();

        // Check if any reads failed (e.g., sensor disconnected)
        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from DHT sensor!");
            
            // --- Display State 1: ERROR ---
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("!! SENSOR ERROR !!");
            lcd.setCursor(0, 1);
            lcd.print("Check Connection");

            // Update globals to an error value (using mutex)
            if (xSemaphoreTake(xSensorDataMutex, (TickType_t)10) == pdTRUE) {
                glob_temperature = -99.9;
                glob_humidity = -99.9;
                xSemaphoreGive(xSensorDataMutex);
            }

        } else {
            // --- Valid Reading ---
            // Update global variables (using mutex)
            if (xSemaphoreTake(xSensorDataMutex, (TickType_t)10) == pdTRUE) {
                glob_temperature = temperature;
                glob_humidity = humidity;
                xSemaphoreGive(xSensorDataMutex);
            }

            // --- SEND TO QUEUES (New Logic) ---
            // We use xQueueOverwrite to ensure the queue always holds the LATEST value.
            // Even if the receiver is busy, this replaces the old value with the new one.
            xQueueOverwrite(xQueueTempLed, &temperature);
            xQueueOverwrite(xQueueHumiNeo, &humidity);

            //Print to Serial (for debugging)
            Serial.print("Humidity: ");
            Serial.print(humidity);
            Serial.print("%  Temperature: ");
            Serial.print(temperature);
            Serial.println("°C");

            // --- Handle 3 Display States ---

            if (temperature >= TEMP_CRITICAL) {
                // --- Display State 2: CRITICAL ---
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("!! CRITICAL !!");
                lcd.setCursor(0, 1);
                lcd.print("Temp: ");
                lcd.print(temperature);
                lcd.print("C");

                // Release the semaphore to signal an alert (critical)
                if(local_alert == false){
                    xSemaphoreGive(xSemaphoreSensorAlert);
                    local_alert = true;
                }
                

            } else if (temperature >= TEMP_WARNING) {
                // --- Display State 3: WARNING ---
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("! WARNING !");
                lcd.setCursor(0, 1);
                lcd.print("Temp: ");
                lcd.print(temperature);
                lcd.print("C");
                //turn off alert semaphore
                if(local_alert == true){
                    xSemaphoreGive(xSemaphoreSensorAlert);
                    local_alert = false;
                }
                
            } else {
                // --- Display State 4: NORMAL ---
                lcd.clear();
                lcd.setCursor(0, 0); // Col 0, Row 0
                lcd.print("Temp: ");
                lcd.print(temperature);
                lcd.print("C");
                
                lcd.setCursor(0, 1); // Col 0, Row 1
                lcd.print("Humi: ");
                lcd.print(humidity);
                lcd.print("%");
                //turn off alert semaphore
                if(local_alert == true){
                    xSemaphoreGive(xSemaphoreSensorAlert);
                    local_alert = false;
                }

            }
        }

        // Wait 5 seconds before the next sensor reading
        vTaskDelay(5000);
    }
}


