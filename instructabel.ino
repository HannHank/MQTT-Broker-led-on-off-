#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
// replace with your wifi ssid and wpa2 key
#define ssid "*************"
#define pass "***************"
// ihr müsst eure sever id eintragen
#define server "*************"
#define port  15083
#define user "*****"
#define pw "*********"
#define client_name "******"
 
#define R1 15

 
void callback(char* topic, byte* payload, unsigned int length);
 
WiFiClient WClient;
PubSubClient client(server, port, callback, WClient);
 
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  byte* p = (byte*)malloc(length);
  //Byte to String
  std::string pl( reinterpret_cast<char const*>(payload), length ) ;
  char* channel = "";
 
  if (pl == "R1_1") {
    digitalWrite(R1, HIGH);
     digitalWrite(R8, HIGH);
    channel = "SH1/actor/out";
  } else if (pl == "R1_0") {
    digitalWrite(R1, LOW);
     digitalWrite(R8, LOW);
    channel = "SH1/actor/out";
  }
 
  // Copy the payload to the new buffer
  memcpy(p, payload, length);
 
  client.publish(channel, p, length);
  // Free the memory
  free(p);
}
 
void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
 
  pinMode(R1, OUTPUT);
  
  digitalWrite(R1, LOW);
  
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
 
  if (client.connect(client_name, user, pw)) {
    client.subscribe("SH1/actor/in");
  }
}
 
void loop()
{
  client.loop();
}
