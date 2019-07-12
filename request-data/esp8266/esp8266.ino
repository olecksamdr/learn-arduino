#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Wifi credentials
const char* ssid = "Apiko";
const char* password = "use_your_skills";

const byte rxPin = D6;
const byte txPin = D5;

unsigned long settingSyncInterval = 1000;
unsigned long lastSettingSync = 0;

SoftwareSerial softSerial(rxPin, txPin);
HTTPClient http;
StaticJsonDocument<200> doc;

// TODO: add comments
void connectToWifi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to the WiFi network");
}

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  softSerial.begin(9600);
  Serial.begin(9600);

  Serial.println();

  connectToWifi(ssid, password);
}

void loop() {
    // sync settings from server
    if (millis() - lastSettingSync >= settingSyncInterval || lastSettingSync == 0) {
      lastSettingSync = millis();
      http.begin("192.168.0.105", 3000, "/api");

       if (http.GET() == HTTP_CODE_OK) {
        String json = http.getString();
        DeserializationError error = deserializeJson(doc, json);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.c_str());
          return;
        }

        Serial.print("Setting sync: ");
        Serial.print(json);
        softSerial.print(json);
        softSerial.println();
      }
    }
}
