#include <ArduinoJson.h>
#include <SoftwareSerial.h>

const byte rxPin = 5;
const byte txPin = 6;

SoftwareSerial softSerial(rxPin, txPin);
StaticJsonDocument<200> doc;

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  softSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (softSerial.available()) {
    String json = softSerial.readStringUntil('\n');
    Serial.print("Setting sync: ");
    Serial.println(json);

    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    Serial.print("lightThreshold: ");
    Serial.println(doc["lightThreshold"].as<unsigned int>());

    Serial.print("wetThreshold: ");
    Serial.println(doc["wetThreshold"].as<unsigned int>());

    Serial.print("timeForPomp: ");
    Serial.println(doc["timeForPomp"].as<unsigned long>());

    Serial.print("syncInterval: ");
    Serial.println(doc["syncInterval"].as<unsigned int>());
  }
}
