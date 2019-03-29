#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <EspMQTTClient.h>


void Wifi();
EspMQTTClient client(
  "OnePlus 3T",                 // Wifi ssid
  "8ea1f2c1878f",                 // Wifi password
  Wifi,// Connection established callback
  "mycube.dscloud.me",                   // MQTT broker ip
  1884,                   // MQTT broker port
  "dietpi",              // MQTT username
  "infected",             // MQTT password
  "3M",                 // Client name
  true,                   // Enable web updater
  true                    // Enable debug messages
);

//String temp = "3M_temp";
//String value = "27.5";
char myOutput[100];


void setup()
{
  Serial.begin(115200);
  Wifi();
}

 void onConnectionEstablished(String temp, String value)
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
  
  while(Serial.available()>0)
  {
    String value;
    String str = Serial.readStringUntil(char(10));
    Serial.println("MQTT");

    if(str.startsWith("T:"));
    {
      value = str.substring(2,7);
      onConnectionEstablished("T_3M", value);
    }
    if(str.startsWith("H:"))
    {
      value = str.substring(2,7);
      onConnectionEstablished("H_3M", value);
    }
   }
}
