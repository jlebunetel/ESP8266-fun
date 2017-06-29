/*
   send data to Kinto
*/

// libraries
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>

// Kinto configuration
char server[] = "https://kinto.dev.mozaws.net/v1";
char fingerprint[] = "CF:8A:24:95:49:F0:5A:1F:3B:EB:15:C0:72:F4:C9:D6:19:3F:EC:FB"; // needed for a HTTPS connection
char token[] = "login";
char secret[] = "password";
char bucket[] = "default";
char collection[] = "sensors";

void kinto_post(String key, String value) {
  String url = String(server) + "/buckets/" + String(bucket) + "/collections/" + String(collection) + "/records";
  String json = "{\"data\": {\"key\": \"" + key + "\", \"value\": \"" + value + "\"}}";
  HTTPClient http;
  http.begin(url, fingerprint);
  http.addHeader("Content-Type", "application/json");
  http.setAuthorization(token, secret);
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
}

void setup() {
  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");
  Serial.println("connected...yeey :)");

  // send a message on start
  kinto_post("board", "on");
}

void loop() {
}
