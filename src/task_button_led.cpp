#include "task_button_led.h"
#include "global.h" // To access buttonQueue

// Define GPIOs based on PDF List of Items Used
#define BOOT_BUTTON_PIN 0  // [cite: 27]
#define LED_PIN 48         // [cite: 28]

// --- Task 1: Sender (Button) ---
// Monitors GPIO 0, debounces, and sends message to queue
void taskButtonSender(void *pvParameters) {
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP); // GPIO 0 is usually PullUp

  int msg = 1; // Message to send

  for (;;) {
    // Detect Press (Active LOW) [cite: 37]
    if (digitalRead(BOOT_BUTTON_PIN) == LOW) {
      // Software Debounce: wait 50ms and check again [cite: 37]
      vTaskDelay(pdMS_TO_TICKS(50));
      
      if (digitalRead(BOOT_BUTTON_PIN) == LOW) {
        Serial.println("Button press detected! Sending message...");
        
        // Send message to Queue [cite: 39]
        // xQueueSend(queue, item, wait_time)
        if (xQueueSend(buttonQueue, &msg, portMAX_DELAY) == pdPASS) {
             Serial.println("Message sent successfully.");
        }

        // Wait for release to prevent sending multiple messages for a single long press [cite: 40]
        while (digitalRead(BOOT_BUTTON_PIN) == LOW) {
          vTaskDelay(pdMS_TO_TICKS(10));
        }
        Serial.println("Button released.");
      }
    }
    vTaskDelay(pdMS_TO_TICKS(10)); // Yield CPU
  }
}

// --- Task 2: Receiver (LED) ---
// Waits for queue data and toggles LED
void taskLedReceiver(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  int ledState = LOW; // Initial state
  int receivedMessage;

  for (;;) {
    // Blocks here until data arrives [cite: 42, 60]
    // This consumes zero CPU cycles while waiting [cite: 43]
    if (xQueueReceive(buttonQueue, &receivedMessage, portMAX_DELAY) == pdPASS) {
      
      // Toggle State [cite: 44, 63]
      ledState = !ledState; 
      digitalWrite(LED_PIN, ledState);

      if (ledState == HIGH) {
        Serial.println("LED On");
      } else {
        Serial.println("LED Off");
      }
    }
  }
}