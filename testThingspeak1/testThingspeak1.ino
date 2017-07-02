#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
const char* ssid ="CoE-C1";
const char* password = "publicwifi";

const char* myWriteAPIKey ="10LK742KO0VNQZKU"; // Write Data
unsigned long myChannelID =296103;
WiFiClient client ;

int buttonPushCounter=0;
int buttonState=0;
int lastButtonState=0;

void setup() {
  pinMode(0,INPUT);
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  //Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
   buttonState = digitalRead(0);
    if(buttonState != lastButtonState)
  {
   if(buttonState == HIGH)
   {
     buttonPushCounter++;
    // Serial.println("Press");
    }
    else {
     // Serial.println("Release");
      if(buttonPushCounter %2 ==0)
   {
      Serial.println("Dang gui 1");
      ThingSpeak.writeField(myChannelID,1,1,myWriteAPIKey);
      delay(15000);
      Serial.println("Done");
    }
    else {
    Serial.println("Dang gui 0");
      ThingSpeak.writeField(myChannelID,1,0,myWriteAPIKey);
      delay(15000);
      Serial.println("Done");
    }
      }
   }
   lastButtonState = buttonState;
}

