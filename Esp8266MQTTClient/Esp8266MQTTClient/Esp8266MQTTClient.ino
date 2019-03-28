#include "ArduinoJson.h"
#include "EspMQTTClient.h"
void onConnectionEstablished();
EspMQTTClient client(
  "iPhone",                 // Wifi ssid
  "mormek5700",                 // Wifi password
  onConnectionEstablished,// Connection established callback
  "mycube.dscloud.me",                   // MQTT broker ip
  1884,                   // MQTT broker port
  "dietpi",              // MQTT username
  "infected",             // MQTT password
  "mathieu.matthieu.mohamed",                 // Client name
  true,                   // Enable web updater
  true                    // Enable debug messages
);

String temp = "temp";
String value = "25.3";
char myOutput[100];


void setup()
{
  Serial.begin(115200);
}

void onConnectionEstablished()
{
  StaticJsonDocument<256> doc;
  doc["name"] = temp.c_str();
  doc["value"] = value.c_str();
  serializeJson (doc, myOutput);

  // Publish a message to "mytopic/test"
  client.publish("data",(char*)myOutput);
}

void loop()
{
  client.loop();
}