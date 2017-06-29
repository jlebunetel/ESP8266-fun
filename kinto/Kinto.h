/*

*/

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

      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, HIGH);
    };

    void post(String key, String value) {
      digitalWrite(LED_BUILTIN, LOW);
      
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
      
      digitalWrite(LED_BUILTIN, HIGH);
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
