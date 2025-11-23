#include "multi_task_task6.h"
#include "global.h"

// --- CẤU HÌNH CHÂN (PIN DEFINITIONS) ---
#define BUTTON_PIN 0 
#define RGB_PIN 45
#define NUMPIXELS 1

// Biến toàn cục
Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);
bool buttonPressed = false;

// --- TASK 1: LED onboard ---
void TaskBlinkOnboard(void *pvParameters) {
  pixels.begin();
  pixels.setBrightness(50);

  while(1) {
    // Bật đèn xanh
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); 
    pixels.show(); // Lệnh bắt buộc để đẩy màu ra đèn
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    // Bật đèn đỏ
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

// --- TASK 2: in chữ ---
void TaskVirtualLED(void *pvParameters) {
  while(1) {
    Serial.println("\n>>> Đèn chớp <<<");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

// --- TASK 3: BUTTON ---
void TaskButton(void *pvParameters) {
  pinMode(BUTTON_PIN, INPUT_PULLUP); 

  while(1) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      if (!buttonPressed) {
        // Bật cả 2 loại đèn sáng TRẮNG
        pixels.setPixelColor(0, pixels.Color(200, 200, 200));
        pixels.show();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        buttonPressed = true;
      }
    } else {
      buttonPressed = false;
    }
    vTaskDelay(20 / portTICK_PERIOD_MS); 
  }
}


// --- SETUP ---

// --- LOOP ---
// void loop() {
// vTaskDelete(NULL); 
// }