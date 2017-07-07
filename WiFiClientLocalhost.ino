/*
 NodeMCU sẽ là WiFiClient gửi HTTP request đến Xampp Server để đọc trạng thái của trang status.php. 
 Nếu giá trị đọc được là |1 thì bật LED GPIO16, nếu là |0 thì tắt LED GPIO16
 Tham khảo từ WiFiClent Example Code
 */
#include <ESP8266WiFi.h>
const char* ssid     = "CoE-C1";
const char* password = "publicwifi";

const char* host = "iot09.tapit.vn";  //Laptop's IP Address // cai nay


void setup() {
  pinMode(16,OUTPUT);
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
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
void loop() {
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {  
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/controlLED/status.php";// fix cai nay
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
               
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){ //hàm client.available() trả về số byte dữ liệu được response từ Server
                             //Serial.println(client.available()); Có thể chèn câu lệnh này để xem được số bytes trả về từ Server (trong bài này là 219 bytes)
    String line = client.readString();
    Serial.print(line);  
    if(line.indexOf("|1")  != -1) digitalWrite(16,LOW);
    if(line.indexOf("|0")  != -1) digitalWrite(16,HIGH);
  }
  Serial.println();
  Serial.println("closing connection");
}
