#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// WiFi credentials
const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WiFiUDP udp;
// Debian server IP
//IPAddress remoteIP(192, 168, 0, 1);
// queue server ip
IPAddress remoteIP(xxx, xxx, xxx, xxx);
const unsigned int remotePort = 2600;  

// Button pin
const int buttonPin = D2;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Set up button pin as input with internal pull-up
  pinMode(buttonPin, INPUT_PULLUP); // Active LOW button

  Serial.println("Ready to send UDP packets to Debian server...");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    sendUDP(3);       // Always send "3"
    delay(300);       // Debounce delay
  }
}

void sendUDP(int value) {
  String message = String(value) + "\n";  // add newline
  udp.beginPacket(remoteIP, remotePort);
  udp.write(message.c_str());
  udp.endPacket();
  Serial.println("Sent UDP: " + message);
}
