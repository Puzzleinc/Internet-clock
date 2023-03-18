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


// Clock variable
unsigned long timeLast = 0;
unsigned long previousMillis = 0;
unsigned long intervalDays = 2*24*60*60*1000; // 2 Days interval
unsigned long intervalSec = 2; // 2 Days interval

// set your starting hour here, not below at int hour. This ensures accurate daily correction of time

uint8_t seconds;
uint8_t minutes;
uint8_t hours;
uint8_t days;

void updateTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t days);
void showTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t days);

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

  timeClient.update();
  seconds = timeClient.getSeconds();
  minutes = timeClient.getMinutes();
  hours = timeClient.getHours();
}

void loop() {
  // Millis Function #1
  unsigned long currentMillis = millis() / 1000;  // the number of milliseconds that have passed since boot
  seconds = currentMillis - previousMillis;

  //the number of seconds that have passed since the last time 60 seconds was reached.
  if (seconds == 60) {
    previousMillis = currentMillis;
    seconds = 0;
    minutes = minutes + 1; 
  }

  //if one minute has passed, start counting milliseconds from zero again and add one minute to the clock.
  if (minutes == 60){
    minutes = 0;
    hours = hours + 1; 
  }

  if (hours == 24){
    hours = 0;
    days = days + 1; 
  }

  // if one hour has passed, start counting minutes from zero and add one hour to the clock
  if (days == intervalDays){
    timeClient.update();
    hours = timeClient.getHours();
    minutes = timeClient.getMinutes();
    seconds = timeClient.getSeconds();
  }

  if (currentMillis - timeLast >= intervalDays) {
    // save the last time you ran the function
    timeLast = currentMillis;

    // call the function
    updateTime(seconds, minutes, hours, days);
  }

  if (currentMillis - timeLast >= intervalSec) {
    // save the last time you ran the function
    timeLast = currentMillis;

    // call the function
    showTime(seconds, minutes, hours, days);
  }

  // timeClient.update();

  // Serial.print(daysOfTheWeek[timeClient.getDay()]);
  // Serial.print(", ");
  // Serial.print(timeClient.getEpochTime());
  // Serial.println(",");
  // Serial.print(timeClient.getHours());
  // Serial.print(":");
  // Serial.print(timeClient.getMinutes());
  // Serial.print(":");
  // Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

  // delay(1000);
  // Serial.println(currentTime);
}

void updateTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t days) {
  // your code here
  timeClient.update();
  seconds = timeClient.getSeconds();
  minutes = timeClient.getMinutes();
  hours = timeClient.getHours();
}

void showTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t days) {
  // your code here
  timeClient.update();
  Serial.print("Waktu internal: ");
  Serial.print(days);
  Serial.print(":");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  Serial.print(" -- ");
  Serial.println("Waktu internet : " + timeClient.getFormattedTime());
}
