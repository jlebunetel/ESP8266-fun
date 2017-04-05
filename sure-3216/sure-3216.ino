/*

*/


#define SCREEN_WIDTH   32
#define SCREEN_HEIGHT  16
#define SCREEN_COLOR    4
#define BUFFER_LENGHT 128

uint8 buffer0[BUFFER_LENGHT];
uint8 buffer1[BUFFER_LENGHT];


uint8 bufferTemp[BUFFER_LENGHT]; // utilisé pour le scroll


uint8 SMILE_8x8 [] = {
  0b00111100,
  0b01000010,
  0b10101001,
  0b10000101,
  0b10000101,
  0b10101001,
  0b01000010,
  0b00111100
};




void setup() {
  Serial.begin(115200);
  Serial.println("hello world !");

  // put your setup code here, to run once:
  pinMode(14, OUTPUT); // DATA
  pinMode(12, OUTPUT); // CS
  pinMode(13, OUTPUT); // WR
  pinMode(15, OUTPUT); // CLK

  // initialisation de la matrice de led
  InitHT1632C();

  ClearBufferHT1632(buffer0);
  for (int x = 5; x < 12 ; x++) {
    for (int y = 2; y < 11; y++) {
      SetPixelHT1632(buffer0, x, y, 1);

    }
  }
  for (int x = 20; x < 23 ; x++) {
    for (int y = 5; y < 9; y++) {
      SetPixelHT1632(buffer0, x, y, 3);

    }
  }

  ClearBufferHT1632(buffer1);
  /*
    for (int x = 10; x < 30 ; x++) {
      for (int y = 5; y < 7; y++) {
        SetPixelHT1632(buffer1, x, y, 2);

      }
    }
    for (int x = 7; x < 10 ; x++) {
      for (int y = 11; y < 15; y++) {
        SetPixelHT1632(buffer1, x, y, 3);

      }
    }
  */

  //SetCharHT1632(buffer1, 'A', 0, 0, 0);
  /*
    SetChar(buffer1, 'J', 1);
    SetChar(buffer1, 'u', 6);
    SetChar(buffer1, 'l', 11);
    SetChar(buffer1, 'i', 32);
    SetChar(buffer1, 'e', 37);
    SetChar(buffer1, 'n', 42);
  */

  SetChar(buffer1, '0', 4);
  SetChar(buffer1, '7', 9);
  SetChar(buffer1, ':', 14);
  SetChar(buffer1, '2', 19);
  SetChar(buffer1, '5', 24);

  for (int i = 0; i < 8 ; i++) {
    buffer1[i + 112] = SMILE_8x8[i];
  }

  ClearBufferHT1632(bufferTemp);

}



void loop() {
  // put your main code here, to run repeatedly:

  RenderHT1632(buffer0);
  delay(2000);

  ScrollLeftHT1632(buffer0, buffer1, 500);

  RenderHT1632(buffer1);
  delay(2000);

  ScrollLeftHT1632(buffer1, buffer0, 500);

  RenderHT1632(buffer0);
  delay(2000);

  ScrollRightHT1632(buffer0, buffer1, 250);

  RenderHT1632(buffer1);
  delay(2000);

  ScrollRightHT1632(buffer1, buffer0, 250);
}


