/*
blink 
turn on and off a led on the pin D7 of the LoLin ESP-12E NodeMcu V3
*/

//int led = 13; // D7 = GPIO13
int led = LED_BUILTIN;

void setup() {
    pinMode(led, OUTPUT);
}

void loop() {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
}
