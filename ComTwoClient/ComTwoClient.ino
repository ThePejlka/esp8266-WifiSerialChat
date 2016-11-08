#include <ESP8266WiFi.h>

char ssid[] = "ssid";                //your wifi SSID
char password[] = "password";        //your wifi password

WiFiClient ComTwo;
IPAddress ofOneIP(192, 168, 0, 101); // Currently manual

void setup() {

  Serial.begin(115200);
  Serial.print("Connecting to: ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)        //connect to wifi
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\n Connected");

  Serial.print("Connecting to server: ");
  Serial.print(ofOneIP);
  while (!ComTwo.connect(ofOneIP, 20))        //connect to server
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n Connected to server");
  Serial.println("\n Waiting for input");

}

void loop() {

  if  (Serial. available() != 0)                      //read anything I wrote, send it to server
  {
    String cliput = Serial.readString();
    Serial.print("You wrote: ");
    Serial.print(cliput);
    ComTwo.print(cliput);
    Serial.println("\n Waiting for input");
  }

  if (ComTwo. available() > 0)                        //read new messages
  {
    Serial.print("Message: ");
    while  (ComTwo. available() > 0)
    {
      char msg = ComTwo.read();
      Serial.print(msg);
    }
    ComTwo.flush();                                  //erase unread messages
    Serial.println("\n Waiting for input");
  }

  if (!ComTwo.connected())                          //reconnect
  {
    ComTwo.connect(ofOneIP, 20);
  }

}
