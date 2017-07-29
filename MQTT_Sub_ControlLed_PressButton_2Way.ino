/* 
  Tran Sang DHBK 0964 500 940
 It connects to an MQTT Localost then:
  - Subscribes to the topic "Light", printing out any messages
    it receives.
  - If the first character of the topic "Light" is '1', switch ON the ESP Led,
    else if '0' switch it off
  - Library: https://github.com/knolleary/pubsubclient/
  - Documentation: https://pubsubclient.knolleary.net/api.html#connect1
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Update these with values suitable for your network.
#define ssid "viettel1234"
#define password "1223334444"
#define mqtt_server "192.168.4.2" // ip v4 - dung ipconfig de xem ip
#define mqtt_topic_pub "Light"
#define mqtt_topic_sub "Light"
const uint16_t mqtt_port = 1883;// default

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  pinMode(0,INPUT_PULLUP);
    pinMode(16,OUTPUT);
  digitalWrite(16,HIGH);// tat led
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char p=(char)payload[0];
  Serial.print((char)payload[0]);
  
    if(p=='1') 
    {
       digitalWrite(16, LOW); 
      Serial.println(" Turn On LED! " );
    } 
    // if MQTT comes a 1, turn on LED on pin D2
    else if(p=='0')
    {
       digitalWrite(16, HIGH); 
      Serial.println(" Turn Off LED! " );
    }
    else Serial.println(" Khong hop le");
    Serial.println();
  }

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(mqtt_topic_pub, "ESP_reconnected");
      // ... and resubscribe
      client.subscribe(mqtt_topic_sub);      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if(digitalRead(0) == LOW)
  {
    while(digitalRead(0) == LOW);
    int statusLed = digitalRead(16);
    if(statusLed == HIGH)// dang tat
    {
      client.publish(mqtt_topic_pub,"1");//de bat
      }
      else {//dang bat
         client.publish(mqtt_topic_pub,"0");// de tat 
        }
    }
  client.loop();
  
}
