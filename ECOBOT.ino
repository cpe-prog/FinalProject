
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 
#include <Firebase.h>
#define FIREBASE_HOST "ecobotproject-9586f-default-rtdb.firebaseio.com"         
#define FIREBASE_AUTH "DEOZcC6qIokR8osdddXq0TwL868SzVhv15PmOSjo"   
#include <Servo.h>


const char* ssid = "realme C12";
const char* password = "00000000";
String command;  
ESP8266WebServer server(80);

Servo servo1; 
Servo servo2;

#define relay1  D2
#define relay2  D0
#define relay3  D1

int value1;
int value2;
int value3;
int value4;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
   pinMode(LED_BUILTIN, OUTPUT);
   
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  servo1.attach(D3);
  servo2.attach(D4);

  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void loop() {

 command = server.arg("State");
  if (command == "A") ON();
  else if (command == "a") OFF();
  else if (command == "B") UPON();
  else if (command == "C") DOWNON();
  else if (command == "D") off();
  else if (command != "S1") {
    int servo1Value = map(command.toInt(), 0, 100, 0, 180); 
    servo1.write(servo1Value); 
  }
  else if (command != "S2") {
    int servo2Value = map(command.toInt(), 0, 100, 0, 180); 
    servo2.write(servo2Value);
  }
  
  server.handleClient();
  
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}

void ON() { 
  digitalWrite(relay1, HIGH);
   digitalWrite(LED_BUILTIN, LOW); 
   delay(5);
}

void OFF() { 
  digitalWrite(relay1, LOW);
   digitalWrite(LED_BUILTIN, HIGH); 
   delay(5);
 
}

void UPON() { 
  digitalWrite(relay2, LOW); 
   digitalWrite(LED_BUILTIN, HIGH); 
   delay(5);
}

void DOWNON() {
  digitalWrite(relay3, LOW);
   digitalWrite(LED_BUILTIN, HIGH); 
   delay(5);

}

void off() {
    digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
   digitalWrite(LED_BUILTIN, LOW); 
   delay(5);

}
