int buttonState=0;
int lastButtonState=0;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(16,OUTPUT);
 digitalWrite(16,1); // tat di
 pinMode(0,INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  { 
    String x = Serial.readString();
    Serial.println(x);
    char y =x.charAt(14);
    char z = x.charAt(15);
    Serial.println("AT+CMGR="+String(y)+String(z));
    delay(200);
    String k = Serial.readString();
    Serial.println(k);
    delay(200);
    String m = Serial.readString();
    if(m.indexOf("BAT") != -1)
    {
      digitalWrite(16,0);//bat led
      }
      else if(m.indexOf("TAT") !=-1)
      {
        digitalWrite(16,1);//tat led
        }
    
  }

//////////
buttonState = digitalRead(0);
    if(buttonState != lastButtonState)
  {
   if(buttonState == HIGH)
   {
    // Serial.println("Press");
    }
    else {
     // Serial.println("Release");
      Serial.println("AT+CMGF=1");// text mode
      delay(200);
      Serial.println("AT+CMGS=\"0964500940\"");
      delay(200);
      Serial.write(0x0D); // enter
      delay(200);
      Serial.println("Press Button");
      delay(200);
      Serial.write(0x1A);// Ctrl+Z
   }
   lastButtonState = buttonState;
}
}
