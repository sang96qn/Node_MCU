#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define Device_1 16
const char *ssid = "viettel1234";
const char *pass = "1223334444";
char auth[]="f5917de376154d138aef86dfe055089f";
void setup()
{
  Serial.begin(9600);
  pinMode(Device_1, OUTPUT);
  pinMode(Device_1 , LOW);
  Blynk.begin(auth,ssid,pass);
}
void loop()
{
  Blynk.run();
}

