#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

WiFiUDP udp;
// Debian server IP
IPAddress remoteIP(192, 168, 0, 105);// change ip address to you server ip
const unsigned int remotePort = 2600;

// Button pins
const int buttonPins[2] = {D2, D5};  // D2 = Senior, D5 = Regular

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

  // Extra safety (sometimes needed on ESP8266 core)
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // Wait for initial connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to WiFi");

  // Initialize buttons
  for (int i = 0; i < 2; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  Serial.println("Ready to send UDP packets to Debian server...");
}

void loop() {
  // No manual reconnect here — handled by event system
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
