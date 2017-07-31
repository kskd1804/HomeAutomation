#include <ESP8266WiFi.h>

//I/O Credentials
int port0 = 14;
int port1 = 12;
int port2 = 13;
int port3 = 5;
int port4 = 4;

//WiFi Credentials
const char* ssid     = "";
const char* password = "";
const char* host = "";

//Device Credentials
String relay_id = "0";

String id[8];
String relay[8];
String device[8];
String device_type[8];
String value[8];
int out[8]= {0,0,0,0,0,0,0,0};
WiFiClient client;
int red = 16;
void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(red,OUTPUT);
  digitalWrite(red,HIGH);
  
  Serial.println("Initalizing ports...");
  pinMode(port0,OUTPUT);
  digitalWrite(port0,HIGH);
  pinMode(port1,OUTPUT);
  digitalWrite(port1,HIGH);
  pinMode(port2,OUTPUT);
  digitalWrite(port2,HIGH);
  pinMode(port3,OUTPUT);
  digitalWrite(port3,HIGH);
  pinMode(port4,OUTPUT);
  digitalWrite(port4,HIGH);
  delay(1000);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(3000);
  Serial.print("Connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
}

void loop() {
   // put your main code here, to run repeatedly:
   if(WiFi.status() == WL_CONNECTED){
    if(!client.connected()){
      if(!client.connect(host,80)){
        Serial.println("Reconnection to host failed!");  
        return;
      }else{
        Serial.println("Connection to host re-established!");  
      }
   }
  delay(2000);
  String postData = "hostname=localhost&username=root&password=&database=arduino&relay_id=0";
  String url = "/arduino/getInput.php";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print("POST ");
  client.print(url);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Cache-Control: no-cache");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(postData.length());
  client.println();
  client.println(postData);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 15000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  int i=0,j=0,x=0,rem=0;
  while(client.available()){
    String line = client.readStringUntil('\n');
    if(x>6){
      switch(rem){
        case 0:
        id[i]=line;
        break;
        case 1:
        relay[i]=line;
        break;
        case 2:
        device[i]=line;
        break;
        case 3:
        device_type[i]=line;
        break;
        case 4:
        value[i]=line;
      }
      j++;
      rem=j%5;
      if(rem==0){
        i++;  
      }  
    }
    x++;
  }
  Serial.println();
  for(x=0;x<i;x++){
    if(relay[x]==relay_id){
       if(device[x]=="0"){
            if(value[x]=="0") out[0] = 0;
            else out[0] = 1;
            Serial.print("Value of device 0 is ");
            Serial.println(value[x]);
            Serial.print("Changing value of device 0 to ");
            Serial.println(out[0]);
            digitalWrite(port0,out[0]);
       }else if(device[x]=="1"){
            if(value[x]=="0") out[1] = 0;
            else out[1] = 1;
            Serial.print("Value of device 1 is ");
            Serial.println(value[x]);
            Serial.print("Changing value of device 1 to ");
            Serial.println(out[1]);
            digitalWrite(port1,out[1]);
       }else if(device[x]=="2"){
            if(value[x]=="0") out[2] = 0;
            else out[2] = 1;
            Serial.print("Value of device 2 is ");
            Serial.println(value[x]);
            Serial.print("Changing value of device 2 to ");
            Serial.println(out[2]);
            digitalWrite(port2,out[2]);
       }else if(device[x]=="3"){
            if(value[x]=="0") out[3] = 0;
            else out[3] = 1;
            Serial.print("Value of device 3 is ");
            Serial.println(value[x]);
            Serial.print("Changing value of device 3 to ");
            Serial.println(out[3]);
            digitalWrite(port3,out[3]);
       }else if(device[x]=="4"){
            if(value[x]=="0") out[4] = 0;
            else out[4] = 1;
            Serial.print("Value of device 4 is ");
            Serial.println(value[x]);
            Serial.print("Changing value of device 4 to ");
            Serial.println(out[4]);
            digitalWrite(port4,out[4]);
       }
     }
   } 
   }else{
    Serial.println();
    Serial.println("Reconnecting to WiFi");
    WiFi.begin(ssid,password); 
    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);  
    }
   }
}
