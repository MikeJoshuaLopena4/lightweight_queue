#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WiFiUDP udp;
// Debian server IP
IPAddress remoteIP(192, 168, 0, 105); //your ip address
const unsigned int remotePort = 2600;

// Button pin
const int buttonPin = D2;  // Single button

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

  pinMode(buttonPin, INPUT_PULLUP);
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

  if (digitalRead(buttonPin) == LOW) {
    sendUDP(3);
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
