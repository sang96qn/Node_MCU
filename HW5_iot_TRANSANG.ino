#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const char *ssid = "viettel1234";
const char* pass = "1223334444";
char auth[] ="97adedf7831747ef8c971f8c6e5a3e6b";

int buttonPushCounter =0;
int buttonState =0;
int lastButtonState=0;
bool isFirstConnect = true;
bool check =false;
BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); 
  if(pinValue == 1)
  check =true;
  else check =false;
  // Serial.println(check);
   buttonPushCounter++;
}

BLYNK_CONNECTED() {
if (isFirstConnect) {
  Blynk.syncAll();
  Blynk.notify("TIMER STARTING!!!!");
isFirstConnect = false;
}
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 pinMode(0,INPUT);
 pinMode(16,OUTPUT);
 digitalWrite(16,1); 
 Blynk.begin(auth,ssid,pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  buttonState = digitalRead(0);
if(buttonState != lastButtonState )
{
  if(buttonState == HIGH)
  {
    buttonPushCounter++;
    }
    else {
    //  Serial.println("Release");
      if(buttonPushCounter %2 ==0)
      {
        Serial.println("Tat led");
        Blynk.virtualWrite(V5,0);
        check = false;
        }
        else {
          Serial.println("Bat led");
        Blynk.virtualWrite(V5,1);
         check =true;
          }
      }
  }
  lastButtonState = buttonState;
  if(check == 1)
  digitalWrite(16,0);
  else digitalWrite(16,1);

}
