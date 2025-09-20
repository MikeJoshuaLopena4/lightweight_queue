#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WiFiUDP udp;
// Debian server IP
IPAddress remoteIP(192, 168, 0, 105);
const unsigned int remotePort = 2600;

// Button pins
const int buttonPins[2] = {D2, D5};  // D2 = Senior, D5 = Regular

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  for (int i = 0; i < 2; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  Serial.println("Ready to send UDP packets to Debian server...");
}

void loop() {
  // Auto reconnect check
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost... reconnecting");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    delay(1000);
    return;
  }

  if (digitalRead(buttonPins[0]) == LOW) {   // Senior
    sendUDP(1);
    delay(300);
  }
  if (digitalRead(buttonPins[1]) == LOW) {   // Regular
    sendUDP(2);
    delay(300);
  }
}

void sendUDP(int value) {
  String message = String(value) + "\n";  
  udp.beginPacket(remoteIP, remotePort);
  udp.write(message.c_str());
  udp.endPacket();
  Serial.println("Sent UDP: " + message);
}
