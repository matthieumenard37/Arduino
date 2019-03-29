#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <EspMQTTClient.h>

#define wifi_ssid "iPhone"
#define wifi_password "mattmatt"

#define mqtt_server "mycube.dscloud.me"
#define mqtt_user "dietpi"
#define mqtt_password "infected"

WiFiClient espClient;
PubSubClient client(espClient);

//Connexion au réseau WiFi

void Wifi() {

 delay(10);

 Serial.println();

 Serial.print("Connexion a ");

 Serial.println(wifi_ssid);  WiFi.begin(wifi_ssid, wifi_password);  while (WiFi.status() != WL_CONNECTED) {

   delay(500);

   Serial.print(".");

 }  Serial.println("");

 Serial.println("Connexion WiFi etablie ");

 Serial.print("=> Addresse IP : ");

 Serial.print(WiFi.localIP());

}


//Reconnexion

void reconnect() {

 //Boucle jusqu'à obtenur une reconnexion

 while (!client.connected()) {

   Serial.print("\nConnexion au serveur MQTT...");

   if (client.connect("T_3M", mqtt_user, mqtt_password)) {

     Serial.println("OK");

   } else {

     Serial.print("KO, erreur : ");

     Serial.print(client.state());

     Serial.println(" On attend 5 secondes avant de recommencer");

     delay(5000);

   }

 }

}


//String temp = "3M_temp";
//String value = "27.5";
char myOutput[100];


void setup()
{
  Serial.begin(115200);
  Wifi();
  client.setServer(mqtt_server, 1884);
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

  if(!client.connected()){
    reconnect();
  }
//  client.loop();
  
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
