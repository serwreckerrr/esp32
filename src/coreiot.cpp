// #include "coreiot.h"

// // ----------- CONFIGURE THESE! -----------
// const char* coreIOT_Server = "app.coreiot.io";  
// const char* coreIOT_Token = "atrrog96dx61e1rqfnhw";   // Device Access Token
// const int   mqttPort = 1883;
// // ----------------------------------------

// WiFiClient espClient;
// PubSubClient client(espClient);


// void reconnect() {
//   Serial.println("No method field in RPC");
//   // Loop until we're reconnected
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     // Attempt to connect (username=token, password=empty)
//     //if (client.connect("ESP32Client", coreIOT_Token, NULL)) {
//     String clientId = "ESP32Client-";
//     clientId += String(random(0xffff), HEX);

//     if (client.connect(clientId.c_str())) {
        
//       Serial.println("connected to CoreIOT Server!");
//       client.subscribe("v1/devices/me/rpc/request/+");
//       Serial.println("Subscribed to v1/devices/me/rpc/request/+");

//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       delay(5000);
//     }
//   }
// }


// void callback(char* topic, byte* payload, unsigned int length) {
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.println("] ");

//   // Allocate a temporary buffer for the message
//   char message[length + 1];
//   memcpy(message, payload, length);
//   message[length] = '\0';
//   Serial.print("Payload: ");
//   Serial.println(message);

//   // Parse JSON
//   StaticJsonDocument<256> doc;
//   DeserializationError error = deserializeJson(doc, message);

//   if (error) {
//     Serial.print("deserializeJson() failed: ");
//     Serial.println(error.c_str());
//     return;
//   }

//   const char* method = doc["method"];
//   if (strcmp(method, "setStateLED") == 0) {
//     // Check params type (could be boolean, int, or string according to your RPC)
//     // Example: {"method": "setValueLED", "params": "ON"}
//     const char* params = doc["params"];

//     if (strcmp(params, "ON") == 0) {
//       Serial.println("Device turned ON.");
//       //TODO

//     } else {   
//       Serial.println("Device turned OFF.");
//       //TODO

//     }
//   } else {
//     Serial.print("Unknown method: ");
//     Serial.println(method);
//   }
// }


// void setup_coreiot(){

//   //Serial.print("Connecting to WiFi...");
//   //WiFi.begin(wifi_ssid, wifi_password);
//   //while (WiFi.status() != WL_CONNECTED) {
  
//   // while (isWifiConnected == false) {
//   //   delay(500);
//   //   Serial.print(".");
//   // }

//   while(1){
//     if (xSemaphoreTake(xBinarySemaphoreInternet, portMAX_DELAY)) {
//       break;
//     }
//     delay(500);
//     Serial.print(".");
//   }


//   client.setServer(CORE_IOT_SERVER.c_str(), CORE_IOT_PORT.toInt());
//   client.setCallback(callback);

// }

// void coreiot_task(void *pvParameters){

//     setup_coreiot();

//     while(1){
//       Serial.println("1");

//         if (!client.connected()) {
//           Serial.println("2");
//             reconnect();
//         }
//         client.loop();

//         // Sample payload, publish to 'v1/devices/me/telemetry'
//         String payload = "{\"temperature\":" + String(glob_temperature) +  ",\"humidity\":" + String(glob_humidity) + "}";
        
//         client.publish("v1/devices/me/telemetry", payload.c_str());

//         Serial.println("3");
        
//         Serial.println("Published payload: " + payload);
//         vTaskDelay(10000);  // Publish every 10 seconds
//     }
// }


































// #include "coreiot.h"

// // ----------- CONFIGURE THESE! -----------
// const char* coreIOT_Server = "app.coreiot.io";  
// const char* coreIOT_Token = "atrrog96dx61e1rqfnhw";   // Device Access Token
// const int   mqttPort = 1883;
// // ----------------------------------------

// #define LED_PIN 48 // Ensure this matches your board

// WiFiClient espClient;
// PubSubClient client(espClient);


// void reconnect() {
//   // Loop until we're reconnected
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     // Attempt to connect (username=token, password=empty)
//     if (client.connect("ESP32Client", coreIOT_Token, NULL)) {
//       Serial.println("connected to CoreIOT Server!");
//       client.subscribe("v1/devices/me/rpc/request/+");
//       Serial.println("Subscribed to v1/devices/me/rpc/request/+");

//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       delay(5000);
//     }
//   }
// }


// void callback(char* topic, byte* payload, unsigned int length) {
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.println("] ");

//   // Allocate a temporary buffer for the message
//   char message[length + 1];
//   memcpy(message, payload, length);
//   message[length] = '\0';
//   Serial.print("Payload: ");
//   Serial.println(message);

//   // Parse JSON
//   StaticJsonDocument<256> doc;
//   DeserializationError error = deserializeJson(doc, message);

//   if (error) {
//     Serial.print("deserializeJson() failed: ");
//     Serial.println(error.c_str());
//     return;
//   }

//   const char* method = doc["method"];
//   if (strcmp(method, "setStateLED") == 0) {//setStateLED
//     // Check params type (could be boolean, int, or string according to your RPC)
//     // Example: {"method": "setValueLED", "params": "ON"}
//     const char* params = doc["params"];

//     if (strcmp(params, "ON") == 0) {
//       Serial.println("Device turned ON.");
//       //TODO
//       digitalWrite(LED_PIN, HIGH);

//     } else {   
//       Serial.println("Device turned OFF.");
//       //TODO
//       digitalWrite(LED_PIN, LOW);

//     }
//   } else {
//     Serial.print("Unknown method: ");
//     Serial.println(method);
//   }
// }


// void setup_coreiot(){
//   pinMode(LED_PIN, OUTPUT);
//   // --- ADD THESE 3 LINES ---;
//   // Serial.print("Connecting to WiFi...");
//   //WiFi.begin(wifi_ssid, wifi_password);
//   //while (WiFi.status() != WL_CONNECTED) {
  
//   // while (isWifiConnected == false) {
//   //   delay(500);
//   //   Serial.print(".");                          /////////wifi not connected
//   // }
//   // Serial.println(" connected!");
//   // client.setServer(coreIOT_Server, mqttPort);
//   // client.setCallback(callback);


//   while(1){
//     if (xSemaphoreTake(xBinarySemaphoreInternet, portMAX_DELAY)) {
//       break;
//     }
//     delay(500);
//     Serial.print(".");
//   }


//   Serial.println(" Connected!");

//   client.setServer(coreIOT_Server, mqttPort);
//   client.setCallback(callback);

// }

// void coreiot_task(void *pvParameters){

//     setup_coreiot();

//     while(1){

//         if (!client.connected()) {
//             reconnect();
//         }
//         client.loop();

//         // Sample payload, publish to 'v1/devices/me/telemetry'
//         String payload = "{\"temperature\":" + String(glob_temperature) +  ",\"humidity\":" + String(glob_humidity) + "}";
        
//         client.publish("v1/devices/me/telemetry", payload.c_str());

//         Serial.println("Published payload: " + payload);
//         vTaskDelay(10000);  // Publish every 10 seconds
//     }
// }













//working version

// #include "coreiot.h"

// // --- Remove hardcoded variables. Use the ones from global.h ---
// WiFiClient espClient;
// PubSubClient client(espClient);

// #define LED_PIN 48 // Ensure this matches your board

// void reconnect() {
//   // Loop until we're reconnected
//   while (!client.connected()) {
//     Serial.print("[CoreIoT] Attempting MQTT connection to: ");
//     Serial.println(CORE_IOT_SERVER);

//     // Use the saved TOKEN from global.h
//     if (client.connect("ESP32Client", CORE_IOT_TOKEN.c_str(), NULL)) {
//       Serial.println("[CoreIoT] Connected to Server!");
//       client.subscribe("v1/devices/me/rpc/request/+");
//     } else {
//       Serial.print("[CoreIoT] Failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       vTaskDelay(5000 / portTICK_PERIOD_MS);
//     }
//   }
// }

// void callback(char* topic, byte* payload, unsigned int length) {
//   Serial.print("[CoreIoT] RPC Message: ");
//   String message;
//   for (int i = 0; i < length; i++) message += (char)payload[i];
//   Serial.println(message);

//   StaticJsonDocument<256> doc;
//   DeserializationError error = deserializeJson(doc, message);

//   if (error) {
//     Serial.print("[CoreIoT] JSON Error: ");
//     Serial.println(error.c_str());
//     return;
//   }

//   const char* method = doc["method"];
//   if (strcmp(method, "setStateLED") == 0) {
//     const char* params = doc["params"];
//     bool isOn = (strcmp(params, "ON") == 0);
//     digitalWrite(LED_PIN, isOn ? HIGH : LOW);
//     Serial.println(isOn ? "LED turned ON" : "LED turned OFF");
//   }
// }

// void setup_coreiot() {
//   Serial.println("[CoreIoT] Task Started. Waiting for WiFi...");

//   // 1. BLOCK here until task_wifi says we are connected
//   // We use the Semaphore, NOT the boolean variable
//   xSemaphoreTake(xBinarySemaphoreInternet, portMAX_DELAY);
  
//   Serial.println("[CoreIoT] WiFi Signal Received! Configuring MQTT...");
  
//   // 2. Put the semaphore back in case other tasks need to check connection
//   xSemaphoreGive(xBinarySemaphoreInternet);

//   // 3. Check if credentials exist
//   if (CORE_IOT_SERVER.isEmpty()) {
//     Serial.println("[CoreIoT] ERROR: CORE_IOT_SERVER is empty. Check info.dat!");
//   }

//   int port = CORE_IOT_PORT.toInt();
//   if (port == 0) port = 1883;

//   client.setServer(CORE_IOT_SERVER.c_str(), port);
//   client.setCallback(callback);
// }

// void coreiot_task(void *pvParameters) {
//   // Small delay to let other tasks initialize
//   vTaskDelay(1000 / portTICK_PERIOD_MS);

//   setup_coreiot();

//   while (1) {
//     if (!client.connected()) {
//       reconnect();
//     }
//     client.loop();

//     // 4. Publish Telemetry
//     String payload = "{\"temperature\":" + String(glob_temperature) + 
//                      ",\"humidity\":" + String(glob_humidity) + "}";
    
//     // Only print if actually connected to avoid spamming
//     if(client.connected()) {
//         client.publish("v1/devices/me/telemetry", payload.c_str());
//         Serial.println("[CoreIoT] Sent: " + payload);
//     }

//     vTaskDelay(10000 / portTICK_PERIOD_MS);
//   }
// }




















// //version with working led control but unreliable and laggy
// #include "coreiot.h"

// WiFiClient espClient;
// PubSubClient client(espClient);

// // Verify your pin! S3=48, C3=8, Generic=2
// #ifndef LED_PIN
// #define LED_PIN 48 
// #endif

// unsigned long lastTelemetrySend = 0;

// void reconnect() {
//   while (!client.connected()) {
//     Serial.print("[CoreIoT] Connecting to MQTT...");
//     if (client.connect("ESP32Client", CORE_IOT_TOKEN.c_str(), NULL)) {
//       Serial.println("Connected!");
//       // Critical: We must resubscribe every time we reconnect
//       client.subscribe("v1/devices/me/rpc/request/+");
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5s");
//       vTaskDelay(5000 / portTICK_PERIOD_MS);
//     }
//   }
// }

// void callback(char* topic, byte* payload, unsigned int length) {
//   String message;
//   for (int i = 0; i < length; i++) message += (char)payload[i];
  
//   Serial.print("[CoreIoT] RPC Received: ");
//   Serial.println(message);

//   StaticJsonDocument<256> doc;
//   DeserializationError error = deserializeJson(doc, message);
//   if (error) return;

//   const char* method = doc["method"];
//   bool ledState = false;

//   // Handle boolean (true/false) or String ("ON"/"OFF")
//   if (doc["params"].is<bool>()) {
//       ledState = doc["params"];
//   } else {
//       const char* paramStr = doc["params"];
//       if (strcmp(paramStr, "ON") == 0) ledState = true;
//   }

//   // Accept "setStateLED" OR "setValue" (common default)
//   if (strcmp(method, "setStateLED") == 0 || strcmp(method, "setValue") == 0) {
//     digitalWrite(LED_PIN, ledState ? HIGH : LOW);
//     Serial.println(ledState ? ">> LED ON" : ">> LED OFF");
    
//     // Optional: Send update back to dashboard to sync switch state
//     String responseTopic = String(topic);
//     responseTopic.replace("request", "response");
//     client.publish(responseTopic.c_str(), ledState ? "true" : "false");
//   }
// }

// void setup_coreiot() {
//   pinMode(LED_PIN, OUTPUT);
//   digitalWrite(LED_PIN, LOW); 

//   xSemaphoreTake(xBinarySemaphoreInternet, portMAX_DELAY);
//   xSemaphoreGive(xBinarySemaphoreInternet);

//   int port = CORE_IOT_PORT.toInt();
//   if (port == 0) port = 1883;

//   client.setServer(CORE_IOT_SERVER.c_str(), port);
//   client.setCallback(callback);
// }

// void coreiot_task(void *pvParameters) {
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   setup_coreiot();

//   while (1) {
//     if (!client.connected()) reconnect();
    
//     // 1. CRITICAL: Run this FREQUENTLY to catch incoming messages
//     client.loop();

//     // 2. Timer Logic: Only send data every 10 seconds (10000ms)
//     unsigned long now = millis();
//     if (now - lastTelemetrySend > 10000) {
//       lastTelemetrySend = now;
      
//       String payload = "{\"temperature\":" + String(glob_temperature) + 
//                        ",\"humidity\":" + String(glob_humidity) + "}";
//       client.publish("v1/devices/me/telemetry", payload.c_str());
//       // Serial.println("Telemetry Sent"); // Uncomment to debug sending
//     }

//     // 3. Short delay prevents CPU hogging, but keeps us responsive
//     vTaskDelay(10 / portTICK_PERIOD_MS);
//   }
// }














#include "coreiot.h"

WiFiClient espClient;
PubSubClient client(espClient);

// Verify your pin! S3=48, C3=8, Generic=2
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















// #include "coreiot.h"

// WiFiClient espClient;
// PubSubClient client(espClient);

// //led pin
// #ifndef LED_PIN
// #define LED_PIN 48 
// #endif

// volatile bool pendingLedUpdate = false;
// volatile bool pendingLedValue  = false;

// unsigned long lastTelemetrySend = 0;

// void reconnect() {
//   while (!client.connected()) {
//     Serial.print("[CoreIoT] Connecting to MQTT...");
//     if (client.connect("ESP32Client", CORE_IOT_TOKEN.c_str(), NULL)) {
//       Serial.println("Connected!");
//       // Critical: We must resubscribe every time we reconnect
//       client.subscribe("v1/devices/me/rpc/request/+");
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5s");
//       vTaskDelay(5000 / portTICK_PERIOD_MS);
//     }
//   }
// }

// void callback(char* topic, byte* payload, unsigned int length) {
//   String message;
//   for (int i = 0; i < length; i++) message += (char)payload[i];
  
//   Serial.print("[CoreIoT] RPC Received: ");
//   Serial.println(message);

//   StaticJsonDocument<256> doc;
//   DeserializationError error = deserializeJson(doc, message);
//   if (error) return;

//   const char* method = doc["method"];
//   bool ledState = false;

//   // Handle boolean (true/false) or String ("ON"/"OFF")
//   if (doc["params"].is<bool>()) {
//       ledState = doc["params"];
//   } else {
//       const char* paramStr = doc["params"];
//       if (strcmp(paramStr, "ON") == 0) ledState = true;
//   }

//   // Accept "setStateLED" OR "setValue" (common default)
//   if (strcmp(method, "setStateLED") == 0 || strcmp(method, "setValue") == 0) {
//     //Do NOT toggle LED here — just store the requested state
//     pendingLedValue  = ledState;
//     pendingLedUpdate = true;

//     Serial.print(">> LED state stored (pending): ");
//     Serial.println(ledState ? "ON" : "OFF");

//     // Send update back to dashboard immediately
//     String responseTopic = String(topic);
//     responseTopic.replace("request", "response");
//     client.publish(responseTopic.c_str(), ledState ? "true" : "false");
//   }
// }

// void setup_coreiot() {
//   pinMode(LED_PIN, OUTPUT);
//   digitalWrite(LED_PIN, LOW); 

//   xSemaphoreTake(xBinarySemaphoreInternet, portMAX_DELAY);
//   xSemaphoreGive(xBinarySemaphoreInternet);

//   int port = CORE_IOT_PORT.toInt();
//   if (port == 0) port = 1883;

//   client.setServer(CORE_IOT_SERVER.c_str(), port);
//   client.setCallback(callback);
// }

// void coreiot_task(void *pvParameters) {
//   vTaskDelay(1000 / portTICK_PERIOD_MS);
//   setup_coreiot();

//   while (1) {
//     if (!client.connected()) reconnect();
    
//     // 1. CRITICAL: Run this FREQUENTLY to catch incoming messages
//     client.loop();

//     // 4. Publish Telemetry
//     String payload = "{\"temperature\":" + String(glob_temperature) + 
//                      ",\"humidity\":" + String(glob_humidity) + "}";
    
//     // Only print if actually connected to avoid spamming
//     if(client.connected()) {
//         client.publish("v1/devices/me/telemetry", payload.c_str());
//         Serial.println("[CoreIoT] Sent: " + payload);
//     }
    
    
    
//     // Apply pending LED state after the task finishes its delays/work
//     if (pendingLedUpdate) {
//       digitalWrite(LED_PIN, pendingLedValue ? HIGH : LOW);
//       Serial.println(pendingLedValue ? ">> LED ON (applied)" : ">> LED OFF (applied)");
//       pendingLedUpdate = false;
//     }




      
//     // 3. Short delay prevents CPU hogging, but keeps us responsive
//     vTaskDelay(10000 / portTICK_PERIOD_MS);
//   }
// }







