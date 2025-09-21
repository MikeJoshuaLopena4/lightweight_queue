#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

WiFiUDP udp;
// Debian server IP
IPAddress remoteIP(192, 168, 0, 105);//change ip address to you server ip
const unsigned int remotePort = 2600;

// Button pin
const int buttonPin = D2;  // Single button

// WiFi event handler
WiFiEventHandler wifiDisconnectHandler;

// === Event callback when WiFi disconnects ===
void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println("⚠️ Disconnected from WiFi, retrying...");
  WiFi.disconnect();
  WiFi.begin(ssid, password);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Register event handler for disconnection
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  // Optional safety (sometimes helps on ESP8266 core versions)
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // Wait for first connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to WiFi");

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("Ready to send UDP packets to Debian server...");
}

void loop() {
  // No need for reconnect logic here — handled by event
  if (digitalRead(buttonPin) == LOW) {
    sendUDP(3);
    delay(300); // debounce
  }
}

void sendUDP(int value) {
  String message = String(value) + "\n";  
  udp.beginPacket(remoteIP, remotePort);
  udp.write(message.c_str());
  udp.endPacket();
  Serial.println("Sent UDP: " + message);
}
