#include <ESP8266WiFi.h>

char ssid[] = "espchat";
char password[] = "123456789";

WiFiServer ComOne(20);

IPAddress OneIP(10, 168, 4, 22);
IPAddress gateway(10,1,1,1);
IPAddress subnet(255,255,255,0);

void setup() {

  Serial.begin(115200) ;
  
  Serial.print("ssid : "); //Print WiFi info
  Serial.print(ssid);
  Serial.print("\npassword: ");
  Serial.print(password);
  Serial.print("\nCreating Acces point.");

  while (!WiFi.softAP(ssid, password)) //Create AP, check if created
  {
    Serial.print(".");
    delay(1000);
  }
  
  WiFi.softAPConfig(OneIP, gateway, subnet); //Configure AP, mainly for IP
  ComOne.begin();
  Serial.print("\nServer started on:  "); //Print IP
  Serial.println(OneIP);

  Serial.println("\n Waiting for input");

}

void loop() {

  WiFiClient ComCli = ComOne.available(); 

  while (ComCli) { 
    if  (Serial. available() != 0) //Read from Serial, send to Client
    {
      String serput = Serial.readString();
      Serial.print("You wrote: ");
      Serial.print(serput);
      ComCli.print(serput);
      Serial.println("\n Waiting for input");
    }

    if (ComCli. available() > 0) //Check for incoming messages
    {
      Serial.print("Message: ");
      while  (ComCli. available() > 0)
      {
        char msg = ComCli.read();
        Serial.print(msg);
      }
      ComCli.flush(); //Flush to make sure nothing is left
      Serial.println("\n Waiting for input");
    }
  }
}


