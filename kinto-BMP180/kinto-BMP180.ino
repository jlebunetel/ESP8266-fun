/*
  send data from an Adafruit BMP180 pressure and temperature sensor to Kinto
*/

// libraries
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>

// Kinto library
#include "Kinto.h"

// Adafruit libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

// Kinto object creation
Kinto kinto(
  "https://kinto.dev.mozaws.net/v1", // server url
  "login",                           // login
  "password",                        // password
  "default",                         // bucket
  "sensors",                         // collection
  "CF:8A:24:95:49:F0:5A:1F:3B:EB:15:C0:72:F4:C9:D6:19:3F:EC:FB" // server ssl fingerprint needed for a HTTPS connection
);

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);


void setup() {
  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");

  /* Initialise the sensor */
  if (!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    kinto.post("board", "error");
    while (1);
  }

  // send a message on start
  kinto.post("board", "on");
}

void loop() {
  /* Get a new sensor event */
  sensors_event_t event;
  bmp.getEvent(&event);

  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    kinto.post("pressure", String(event.pressure));

    /* First we get the current temperature from the BMP085 */
    float temperature;
    bmp.getTemperature(&temperature);
    kinto.post("temperature", String(temperature));
  }
  else
  {
    kinto.post("board", "error");
  }
  delay(10000);
}
