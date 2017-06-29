/*
   send data to Kinto
*/

// libraries
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>

class Kinto {
  public:

    Kinto(char* server, char* token, char* secret, char* bucket, char* collection, char* fingerprint = "")
    {
      strcpy(this->server, server);
      strcpy(this->fingerprint, fingerprint);
      strcpy(this->token, token);
      strcpy(this->secret, secret);
      strcpy(this->bucket, bucket);
      strcpy(this->collection, collection);
      this->url = String(server) + "/buckets/" + String(bucket) + "/collections/" + String(collection) + "/records";
    };

    void post(String key, String value) {
      String json = "{\"data\": {\"key\": \"" + key + "\", \"value\": \"" + value + "\"}}";
      Serial.print(url);
      HTTPClient http;
      if (server[4] == 's') {
        http.begin(url, fingerprint);
      }
      else {
        http.begin(url);
      }
      http.addHeader("Content-Type", "application/json");
      http.setAuthorization(token, secret);
      http.POST(json);
      http.end();
    };

  private:

    char server[100];
    char fingerprint[100];
    char token[100];
    char secret[100];
    char bucket[100];
    char collection[100];
    String url;
};

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
