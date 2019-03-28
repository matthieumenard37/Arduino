#include "EspMQTTClient.h"

void onConnectionEstablished();

EspMQTTClient client(
  "OnePlus 3T",                 // Wifi ssid
  "8ea1f2c1878f",                 // Wifi password
  onConnectionEstablished,// Connection established callback
  "mycube.dscloud.me",    // MQTT broker ip
  1884,                   // MQTT broker port
  "dietpi",              // MQTT username
  "infected",             // MQTT password
  "mathieu",                 // Client name
  true,                   // Enable web updater
  true                    // Enable debug messages
);



void setup()
{
  Serial.begin(115200);
}

void onConnectionEstablished()
{

  // Publish a message to "mytopic/test"
  client.publish("data",{\"name": "tempTeamN1","value": "25.41"\}
);

  // Execute delayed instructions
  client.executeDelayed(5 * 1000, []() {
    client.publish("mytopic/test", "This is a message sent 5 seconds later");
  });
}

void loop()
{
  client.loop();
}
