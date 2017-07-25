// Them chuc nang cap nhat Wifi

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

SimpleTimer timer;

const char *ssid = "viettel1234";
const char* pass = "1223334444";
char auth[] ="97adedf7831747ef8c971f8c6e5a3e6b";

#define LED 16 // GPIO 16
#define buttonPin 0

int buttonPushCounter =0;
int buttonState =0;
int lastButtonState=0;

bool isFirstConnect = true;
bool check =false;

long startSecond ;
long stopSecond;
long nowSecond;

BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); 
  if(pinValue == 1)
  {
  check =true;
  }
  else 
  {
    check =false;
  }
   buttonPushCounter++;
}

BLYNK_WRITE(V2)
{
  int checkTime = param.asInt();
  if(checkTime ==1)
  {
    check =true;
      Blynk.virtualWrite(V5,1);
    }
    else {
     check =false;
        Blynk.virtualWrite(V5,0);
      }
  }
  
BLYNK_CONNECTED() {
if (isFirstConnect) {
  Blynk.syncAll();
 // Blynk.notify("TIMER STARTING!!!!");
isFirstConnect = false;
}
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 pinMode(buttonPin,INPUT);
 pinMode(LED,OUTPUT);
 digitalWrite(LED,1); 
 Blynk.begin(auth,ssid,pass);
  timer.setInterval(5000L,reconnectBlynk);
}
void checkButton()
{
   buttonState = digitalRead(buttonPin);
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
      //  Serial.println("Tat led");
        Blynk.virtualWrite(V5,0);
        check = false;
        }
        else {
      //    Serial.println("Bat led");
        Blynk.virtualWrite(V5,1);
         check =true;
          }
      }
  }
  lastButtonState = buttonState;
  if(check == 1)
  digitalWrite(LED,0);
  else digitalWrite(LED,1);

  }
  
  void reconnectBlynk() {
  if (!Blynk.connected()) {
    if(Blynk.connect()) {
     BLYNK_LOG("Reconnected");
    } else {
      BLYNK_LOG("Not reconnected");
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
  checkButton();
}
