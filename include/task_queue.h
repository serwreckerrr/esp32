#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// Task function prototypes
void taskButtonSender(void *pvParameters);
void taskLedReceiver(void *pvParameters);

#endif