#include <String.h>
#define LED 16
#define BUTTON 0
int buttonPushCounter=0;
int buttonState=0;
int lastButtonState=0;
int ledStatus;
String data;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(LED,OUTPUT);
 pinMode(BUTTON,INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
   buttonState = digitalRead(BUTTON);
   
   /*Check string*/
 if(Serial.available()){
  while(Serial.available()){
    data= Serial.readString();
     if(data=="LED ON")
     {
      digitalWrite(LED,LOW);
      Serial.write("LED ON");
      Serial.println();
     }
     else if(data=="LED OFF")
     {
     digitalWrite(LED,HIGH);
     Serial.write("LED OFF");
     Serial.println();
     }
  }
 }
 
/*Check button */

 if(buttonState != lastButtonState)
  {
   if(buttonState == HIGH)
   {
     buttonPushCounter++;
    // Serial.println("Press");
    }
    else {
     // Serial.println("Release");
     //
     if(buttonPushCounter %2 ==0)
   {
    digitalWrite(LED,HIGH);// cai den bi nguoc
    Serial.println("Off"); // thi den mau xanh tat
    }
    else {
          digitalWrite(LED,LOW);
    Serial.println("On");
      }
      //
      }
   }
   lastButtonState = buttonState;
   
}
