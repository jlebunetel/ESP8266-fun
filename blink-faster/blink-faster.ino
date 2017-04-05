/*
blink 
turn on and off a led on the pin D7 of the LoLin ESP-12E NodeMcu V3

inspiré de : https://github.com/wdim0/esp8266_direct_gpio

get 6x faster GPIOs !!!
impulse length is around 2 us
*/

#define GPIO13_H         (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<13))
#define GPIO13_L         (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<13))

int led = 13; // D7 = GPIO13

void setup() {
    pinMode(led, OUTPUT);
}

void loop() {
    GPIO13_H;
    delay(2000);
    GPIO13_L;
    delay(1000);
}
