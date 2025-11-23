#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// --- CẤU HÌNH CHÂN (PIN DEFINITIONS) ---
#define LED1_PIN 1    
#define LED2_PIN 2
#define BUTTON_PIN 0  

// Biến toàn cục
bool buttonPressed = false;

// --- TASK 1: LED 1 ---
void TaskBlink1(void *pvParameters) {
  pinMode(LED1_PIN, OUTPUT);
  while(1) {
    digitalWrite(LED1_PIN, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    digitalWrite(LED1_PIN, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// --- TASK 2: LED 2 ---
void TaskBlink2(void *pvParameters) {
  pinMode(LED2_PIN, OUTPUT);
  while(1) {
    digitalWrite(LED2_PIN, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(LED2_PIN, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// --- TASK 3: BUTTON ---
void TaskButton(void *pvParameters) {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  while(1) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      if (!buttonPressed) {
        Serial.println("PlatformIO: Nút đang được nhấn!");
        buttonPressed = true;
      }
    } else {
      buttonPressed = false;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); 
  }
}

// --- SETUP ---
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("--- Bắt đầu chương trình FreeRTOS trên PlatformIO ---");

  // Tạo các Task
  xTaskCreate(TaskBlink1, "Blink 1", 2048, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "Blink 2", 2048, NULL, 1, NULL);
  xTaskCreate(TaskButton, "Button",  2048, NULL, 2, NULL);
}

// --- LOOP ---
void loop() {
  vTaskDelete(NULL); 
}