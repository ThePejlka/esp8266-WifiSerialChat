#include <ESP8266WiFi.h>

char ssid[] = "ssid";
char password[] = "password";

WiFiClient ComTwo;
IPAddress ofOneIP(10, 0, 0, 212); // Currently manual

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

  Serial.print("Connecting to server: ");
  Serial.print(ofOneIP);
  while (!ComTwo.connect(ofOneIP, 20))
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n Connected to server");
  Serial.println("\n Waiting for input");

}

void sendmsg() {}
void getmsg() {}

void loop() {

  if  (Serial. available() != 0)
  {
    String cliput = Serial.readString();
    Serial.print("You wrote: ");
    Serial.print(cliput);
    ComTwo.print(cliput);
    Serial.println("\n Waiting for input");
  }

  if (ComTwo. available() > 0)
  {
    Serial.print("Message: ");
    while  (ComTwo. available() > 0)
    {
      char msg = ComTwo.read();
      Serial.print(msg);
    }
    ComTwo.flush();
    Serial.println("\n Waiting for input");
  }

  if (!ComTwo.connected())
  {
    ComTwo.connect(ofOneIP, 20);
  }

}
