// #include "task_webserver.h"

// AsyncWebServer server(80);
// AsyncWebSocket ws("/ws");

// bool webserver_isrunning = false;

// void Webserver_sendata(String data)
// {
//     if (ws.count() > 0)
//     {
//         ws.textAll(data); // Gửi đến tất cả client đang kết nối
//         Serial.println("📤 Đã gửi dữ liệu qua WebSocket: " + data);
//     }
//     else
//     {
//         Serial.println("⚠️ Không có client WebSocket nào đang kết nối!");
//     }
// }

// void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
// {
//     if (type == WS_EVT_CONNECT)
//     {
//         Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
//     }
//     else if (type == WS_EVT_DISCONNECT)
//     {
//         Serial.printf("WebSocket client #%u disconnected\n", client->id());
//     }
//     else if (type == WS_EVT_DATA)
//     {
//         AwsFrameInfo *info = (AwsFrameInfo *)arg;

//         if (info->opcode == WS_TEXT)
//         {
//             String message;
//             message += String((char *)data).substring(0, len);
//             // parseJson(message, true);
//             handleWebSocketMessage(message);
//         }
//     }
// }

// void connnectWSV()
// {
//     ws.onEvent(onEvent);
//     server.addHandler(&ws);
//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(LittleFS, "/index.html", "text/html"); });
//     server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(LittleFS, "/script.js", "application/javascript"); });
//     server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
//               { request->send(LittleFS, "/styles.css", "text/css"); });
//     server.begin();
//     ElegantOTA.begin(&server);
//     webserver_isrunning = true;
// }

// void Webserver_stop()
// {
//     ws.closeAll();
//     server.end();
//     webserver_isrunning = false;
// }

// void Webserver_reconnect()
// {
//     if (!webserver_isrunning)
//     {
//         connnectWSV();
//     }
//     ElegantOTA.loop();
// }




























#include "task_webserver.h"
#include "global.h" 
#include <ArduinoJson.h>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

bool webserver_isrunning = false;

void Webserver_sendata(String data)
{
    if (ws.count() > 0)
    {
        ws.textAll(data); // Gửi đến tất cả client đang kết nối
        Serial.println("📤 Đã gửi dữ liệu qua WebSocket: " + data);
    }
    else
    {
        Serial.println("⚠️ Không có client WebSocket nào đang kết nối!");
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
    }
    else if (type == WS_EVT_DATA)
    {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;

        if (info->opcode == WS_TEXT)
        {
            String message;
            message += String((char *)data).substring(0, len);
            // parseJson(message, true);
            handleWebSocketMessage(message);
        }
    }
}

// 2. Add this new Task Function
void Task_Broadcast_Sensor(void *pvParameters) {
    while (true) {
        // Only send if clients are connected
        if (ws.count() > 0) {
            StaticJsonDocument<200> doc;
            
            // Take Mutex to ensure we read valid data
            if (xSemaphoreTake(xSensorDataMutex, 100) == pdTRUE) {
                doc["temperature"] = glob_temperature;
                doc["humidity"] = glob_humidity;
                xSemaphoreGive(xSensorDataMutex);
                
                String jsonString;
                serializeJson(doc, jsonString);
                ws.textAll(jsonString); // Send to Browser
                Serial.println("Sent: " + jsonString);
            }
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS); // Send every 2 seconds
    }
}

void connnectWSV()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", "text/html"); });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/script.js", "application/javascript"); });
    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/styles.css", "text/css"); });
    server.begin();
    ElegantOTA.begin(&server);
    webserver_isrunning = true;

    xTaskCreate(Task_Broadcast_Sensor, "Broadcast Task", 4096, NULL, 1, NULL);
}

void Webserver_stop()
{
    ws.closeAll();
    server.end();
    webserver_isrunning = false;
}

void Webserver_reconnect()
{
    if (!webserver_isrunning)
    {
        connnectWSV();
    }
    ElegantOTA.loop();
}
