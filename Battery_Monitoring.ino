#include <ESP8266WiFi.h>

String apiKey = "7AOKOUNF85BAUE4S";
const char* ssid =  "realme C12";
const char* pass =  "00000000";
const char* server = "api.thingspeak.com";

int analogInPin  = A0;
int sensorValue;        
float calibration = 5.0;
int bat_percentage;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  sensorValue = analogRead(analogInPin);
  float voltage = ((sensorValue * 6) / 1024) * 4 + calibration; 

  bat_percentage = map(voltage, 10.8, 24.0, 0, 100); 

  if (bat_percentage >= 100) {
    bat_percentage = 100;
  }
  if (bat_percentage <= 0) {
    bat_percentage = 1;
  }

  Serial.print("Analog Value = ");
  Serial.print(sensorValue);
  Serial.print("\t Output Voltage = ");
  Serial.print(voltage);
  Serial.print("\t Battery Percentage = ");
  Serial.println(bat_percentage);
  delay(1000);

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(voltage);
    postStr += "&field2=";
    postStr += String(bat_percentage);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    delay(100);
    client.print("Host: api.thingspeak.com\n");
    delay(100);
    client.print("Connection: close\n");
    delay(100);
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    delay(100);
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    delay(100);
    client.print("Content-Length: ");
    delay(100);
    client.print(postStr.length());
    delay(100);
    client.print("\n\n");
    delay(100);
    client.print(postStr);
    delay(100);
  }

  client.stop();
  Serial.println("Sending....");
  delay(15000);
}
