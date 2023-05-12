#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "realme C12";
const char* password = "00000000";
String command;  
ESP8266WebServer server(80);

Servo servo1; 
Servo servo2;

#define relay1  D0
#define relay2  D1
#define relay3  D2
#define relay4  D3

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

  servo1.attach(D4);
  servo2.attach(D5);

  pinMode(relay1, OUTPUT); 
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

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
  else if (command == "S1") servoOne(); 
  else if (command == "S2") servoTwo(); 

  server.handleClient();

}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}


void UPON() { 
   digitalWrite(relay1, LOW); 
   digitalWrite(relay3, LOW); 
   digitalWrite(LED_BUILTIN, HIGH); 
   delay(5);
}

void DOWNON() {
   digitalWrite(relay2, LOW);
   digitalWrite(LED_BUILTIN, HIGH); 
   delay(5);

}

void ON() { 
   digitalWrite(relay4, HIGH);
   digitalWrite(LED_BUILTIN, LOW); 
   delay(5);
}

void OFF() { 
   digitalWrite(relay4, LOW);
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

void servoOne(){
    int servo1Value = map(command.toInt(), 0, 1023, 0, 180);
    servo1.write(servo1Value); 
}

void servoTwo(){
    int servo2Value = map(command.toInt(), 0, 1023, 0, 180); 
    servo2.write(servo2Value);
}
