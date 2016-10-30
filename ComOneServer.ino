#include <ESP8266WiFi.h>

char ssid[] = "ssid";
char password[] = "password";

WiFiServer ComOne(20);
IPAddress OneIP;


void setup() {

  Serial.begin(115200);
  Serial.print("Connecting to: ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n Connected");

  ComOne.begin();
  Serial.print("Server started on:  ");
  OneIP = WiFi.localIP();
  Serial.println(OneIP);

  Serial.println("\n Waiting for input");

}

void sendmsg() {}
void getmsg() {}

void loop() {

  WiFiClient ComCli = ComOne.available();
  
  if (ComCli) {
    if  (Serial. available() != 0)
    {
      String serput = Serial.readString();
      Serial.print("You wrote: ");
      Serial.print(serput);
      ComCli.print(serput);
      Serial.println("\n Waiting for input");
    }
ComCli.flush();
    if (ComCli. available() > 0)
    {
      Serial.print("Message: ");
      while  (ComCli. available() > 0)
      {
        char msg = ComCli.read();
        Serial.print(msg);
      }
      ComCli.flush();
      Serial.println("\n Waiting for input");
    }
  }
}


