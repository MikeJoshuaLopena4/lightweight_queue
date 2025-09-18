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

// Button pins
const int buttonPins[2] = {D2, D5};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Set up button pins as input with internal pull-up
  for (int i = 0; i < 2; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Active LOW buttons
  }

  Serial.println("Ready to send UDP packets to Debian server...");
}

void loop() {
  for (int i = 0; i < 2; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      sendUDP(i + 1);   // Send button ID (1, 2)
      delay(300);       // Debounce delay
    }
  }
}

void sendUDP(int buttonID) {
  String message = String(buttonID);
  udp.beginPacket(remoteIP, remotePort);
  udp.write(message.c_str());
  udp.endPacket();
  Serial.println("Sent UDP: " + message);
}
