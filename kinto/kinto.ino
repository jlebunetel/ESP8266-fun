/*
  send data to Kinto
*/

// libraries
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>

// Kinto library
#include "Kinto.h"

// Kinto object creation
Kinto kinto(
  "https://kinto.dev.mozaws.net/v1", // server url
  "login",                           // login
  "password",                        // password
  "default",                         // bucket
  "sensors",                         // collection
  "CF:8A:24:95:49:F0:5A:1F:3B:EB:15:C0:72:F4:C9:D6:19:3F:EC:FB" // server ssl fingerprint needed for a HTTPS connection
);

void setup() {
  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");

  // send a message on start
  kinto.post("board", "on");
}

void loop() {
}
