#include <Arduino.h>
#include <Wire.h>

#include "wificonnect.h"

/* Put your SSID & Password */
const char* ssid;  // Enter SSID here
const char* password;  //Enter Password here
const char* deviceName;

// Initialize Internal led build in
uint8_t connled = 2;

void setup() {
 /*  Common cathode led RGB */
  Serial.begin(115200);

  //  Initialize IO pin -----------------------
  pinMode(connled, OUTPUT);

  //  Connecting to wifi -----------------------
  ssid = "Puzzle24";  // Enter SSID here
  password = "gzcmb94463";  // Enter Password here
  deviceName = "Sensor Pompa"; // DHCP Hostname (useful for finding device for static lease)
  wificonnect(ssid, password, deviceName, connled);

  Serial.println(WiFi.gatewayIP());
}

void loop() {
  // Millis Function #1
  unsigned long currentTime = millis() / 60000;
  //Serial.println(currentTime);
}