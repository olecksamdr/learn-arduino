#include "ESP8266WiFi.h"
#include "PubSubClient.h"

const byte LED = 2;

// Wifi credentials
const char* ssid = "<ssid>";
const char* password = "********";

// Mqtt server credentials
const char* mqttServer = "<server>";
const char* mqttUser = "<user>";
const char* mqttPassword = "<pass>";
const int mqttPort = 12767;

// Uniqe identifier of our client
const char* clientId = "ESP8266Client";

void callback(char* topic, byte* payload, unsigned int length);

WiFiClient espClient;
PubSubClient client(mqttServer, mqttPort, callback, espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  const char message = (char)payload[0];

  // handle message arrived
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(message);

  if (message == '1') {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
}

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

// TODO: add comments
// TODO: implement non-blocking reconect
void connectToMqttServer() {
  Serial.println("Connecting to MQTT server");

  while(!client.connected()) {
    if (client.connect(clientId, mqttUser, mqttPassword)) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed with state: ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.subscribe("led");
}

void setup() {
  pinMode(LED, OUTPUT); 

  // Open a serial connection
  Serial.begin(9600);
  Serial.println();

  connectToWifi(ssid, password);
  connectToMqttServer();
}

void loop() {
  client.loop();
}
