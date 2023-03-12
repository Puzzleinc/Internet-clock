#include <Arduino.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "wificonnect.h"

/* Put your SSID & Password */
const char* ssid;  // Enter SSID here
const char* password;  //Enter Password here
const char* deviceName;

// Initialize Internal led build in
uint8_t connled = 2;

// Iniotialize NTP Class
WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
// NTPClient timeClient(ntpUDP);

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
// NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200, 60000); // Menambahkan variabel langsung pada fungsi
NTPClient timeClient(ntpUDP, "pool.ntp.org");

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


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

  timeClient.begin();
  // Tambahan fungsi
  timeClient.setTimeOffset(25200);
  timeClient.setUpdateInterval(180000);

}

void loop() {
  // Millis Function #1
  unsigned long currentTime = millis() / 60000;

  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getEpochTime());
  Serial.println(",");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

  delay(1000);
  Serial.println(currentTime);
}