#include "coreiot.h"

WiFiClient espClient;
PubSubClient client(espClient);

//led pin
#ifndef LED_PIN
#define LED_PIN 48 
#endif

unsigned long lastTelemetrySend = 0;

void reconnect() {
  while (!client.connected()) {
    Serial.print("[CoreIoT] Connecting to MQTT...");
    if (client.connect("ESP32Client", CORE_IOT_TOKEN.c_str(), NULL)) {
      Serial.println("Connected!");
      // Critical: We must resubscribe every time we reconnect
      client.subscribe("v1/devices/me/rpc/request/+");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5s");
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) message += (char)payload[i];
  
  Serial.print("[CoreIoT] RPC Received: ");
  Serial.println(message);

  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);
  if (error) return;

  const char* method = doc["method"];
  bool ledState = false;

  // Handle boolean (true/false) or String ("ON"/"OFF")
  if (doc["params"].is<bool>()) {
      ledState = doc["params"];
  } else {
      const char* paramStr = doc["params"];
      if (strcmp(paramStr, "ON") == 0) ledState = true;
  }

  // Accept "setStateLED" OR "setValue" (common default)
  if (strcmp(method, "setStateLED") == 0 || strcmp(method, "setValue") == 0) {
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    Serial.println(ledState ? ">> LED ON" : ">> LED OFF");
    
    // Optional: Send update back to dashboard to sync switch state
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    client.publish(responseTopic.c_str(), ledState ? "true" : "false");
  }
}

void setup_coreiot() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); 

  xSemaphoreTake(xBinarySemaphoreInternet, portMAX_DELAY);
  xSemaphoreGive(xBinarySemaphoreInternet);

  int port = CORE_IOT_PORT.toInt();
  if (port == 0) port = 1883;

  client.setServer(CORE_IOT_SERVER.c_str(), port);
  client.setCallback(callback);
}

void coreiot_task(void *pvParameters) {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  setup_coreiot();

  while (1) {
    if (!client.connected()) reconnect();
    
    // 1. CRITICAL: Run this FREQUENTLY to catch incoming messages
    client.loop();

    // 2. Timer Logic: Only send data every 10 seconds (10000ms)
    unsigned long now = millis();
    if (now - lastTelemetrySend > 10000) {
      lastTelemetrySend = now;
      
      String payload = "{\"temperature\":" + String(glob_temperature) + 
                       ",\"humidity\":" + String(glob_humidity) + "}";
      client.publish("v1/devices/me/telemetry", payload.c_str());
      // Serial.println("Telemetry Sent"); // Uncomment to debug sending
    }

    // 3. Short delay prevents CPU hogging, but keeps us responsive
    vTaskDelay(10);
  }
}


