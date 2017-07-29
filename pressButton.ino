void setup() {
  // put your setup code here, to run once:
  pinMode(0,INPUT_PULLUP);// khi khong nhan nut - HIGH
  pinMode(16,OUTPUT);
  digitalWrite(16,1); // tat led
}

void loop() {
  // put your main code here, to run repeatedly:
   if(digitalRead(0)==LOW)
   {
    while(digitalRead(0) ==LOW);// chong nhieu
    int ledStatus = digitalRead(16);
    if(ledStatus ==0){
      digitalWrite(16,HIGH);
    }
    else {
      digitalWrite(16,LOW);
    }
    }
   
}
