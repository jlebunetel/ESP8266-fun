// ce programme ne fait qu'envoyer sur le port série toute commande reçue par le recepteur IR
// testé avec un LinkNode D1 et un TSOP1738

// fonctionne avec la librairie IRremoteESP8266 Version 1.1.1
// by Sebastien Warin, Mark Szabo, Ken Shirriff, David Conran
// https://github.com/markszabo/IRremoteESP8266

// LinkNode D1 Pin Mapping :
//      PIN GPIO
#define D11 13
#define D13 14

#include <IRremoteESP8266.h>
const int RECV_PIN = D11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // la pin D13 est utilisée pour alimenter le récepteur
  pinMode(D13, OUTPUT);
  digitalWrite(D13, HIGH);

  // Start the receiver
  irrecv.enableIRIn();

  Serial.begin(115200);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
