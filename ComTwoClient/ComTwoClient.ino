#include <ESP8266WiFi.h>

char ssid[] = "espchat";  
char password[] = "123456789";

WiFiClient ComTwo;
IPAddress ofOneIP(10, 168, 4, 22);

void setup() {

  Serial.begin(115200);
  Serial.print("Connecting to: ");
  Serial.print(ssid);

  WiFi.begin(ssid, password); //Connect to Wifi

  while (WiFi.status() != WL_CONNECTED) //Check if connected
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\n Connected");

  Serial.print("Connecting to server: ");
  Serial.print(ofOneIP);
  while (!ComTwo.connect(ofOneIP, 20)) //Connect to server
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n Connected to server");
  Serial.println("\n Waiting for input");

}

void loop() {

  if  (Serial. available() != 0) //Read from Serial, send to client on Server
  {
    String cliput = Serial.readString();
    Serial.print("You wrote: ");
    Serial.print(cliput);
    ComTwo.print(cliput);
    Serial.println("\n Waiting for input");
  }

  if (ComTwo. available() > 0) //Check for incoming messages
  {
    Serial.print("Message: ");
    while  (ComTwo. available() > 0)
    {
      char msg = ComTwo.read();
      Serial.print(msg);
    }
    ComTwo.flush(); //Flush to make sure nothing is left
    Serial.println("\n Waiting for input");
  }

  if (!ComTwo.connected())                          //Client may get dissconnected after readingm check and connect again if necessary
  {
    ComTwo.connect(ofOneIP, 20);
  }

}
