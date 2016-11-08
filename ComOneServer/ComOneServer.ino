#include <ESP8266WiFi.h>

char ssid[] = "ssid";                //your wifi SSID
char password[] = "password";        //your wifi password

WiFiServer ComOne(20);
IPAddress OneIP;
WiFiClient Comcli;

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

void loop() {

  WiFiClient ComCli= ComOne.available();                //searching for client
  
  while (ComCli) {
    if  (Serial. available() != 0)                      //read anything I wrote, send it to client
    {
      String serput = Serial.readString();
      Serial.print("You wrote: ");
      Serial.print(serput);
      ComCli.print(serput);
      Serial.println("\n Waiting for input");
    }

    if (ComCli. available() > 0)                        //read new messages
    {
      Serial.print("Message: ");
      while  (ComCli. available() > 0)
      {
        char msg = ComCli.read();
        Serial.print(msg);
      }
      ComCli.flush();                                   //erase unread messages
      Serial.println("\n Waiting for input");
    }
  }
}


