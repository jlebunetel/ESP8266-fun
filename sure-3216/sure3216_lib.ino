// NO-OP Definition
#define CLK_DELAY; __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
// The HT1632 requires at least 50 ns between the change in data and the rising edge of the WR signal.
// On a 80MHz processor, __asm__("nop\n\t"); provides 12.5ns per NOP.
// 5 times provides 62.5ns

// D5 = GPIO14 = Blue = DATA
#define HT1632C_DATA_1     (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<14))
#define HT1632C_DATA_0     (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<14))
#define HT1632C_DATA(x)    ((x)?HT1632C_DATA_1:HT1632C_DATA_0)

// D6 = GPIO12 = Green = CS
#define HT1632C_CS_1       (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<12))
#define HT1632C_CS_0       (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<12))

// D7 = GPIO13 = Yellow = WR
#define HT1632C_WR_1       (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<13))
#define HT1632C_WR_0       (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<13))

// D8 = GPIO15 = Orange = CLK
#define HT1632C_CLK_1      (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<15))
#define HT1632C_CLK_0      (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<15))


//Following definition facilitates compilation of HT1632C control commands.
#define SYS_DIS        0b100000000000 //Turn off both system oscillator and LED duty cycle generator
#define SYS_EN         0b100000000010 //Turn on system oscillator
#define LED_OFF        0b100000000100 //Turn off LED duty cycle generator
#define LED_ON         0b100000000110 //Turn on LED duty cycle generator
#define BLINK_OFF      0b100000010000 //Turn off blinking function
#define BLINK_ON       0b100000010010 //Turn on blinking function
#define SLAVE_MODE     0b100000100000 // Set slave mode and clock source from external clock
#define MASTER_MODE    0b100000101000 // Set master mode and clock source on-chip RC oscillator, the system clock output to OSC pin
#define RC_MASTER_MODE 0b100000110000 // System clock source, on-chip RC oscillator
#define EXT_CLK        0b100000111000 // System clock source, external clock source

#define N_MOS_COM8     0b100001000000 //N-MOS open drain output and 8 common option
#define N_MOS_COM16    0b100001001000 //N-MOS open drain output and 16 common option
#define P_MOS_COM8     0b100001010000 //P-MOS open drain output and 8 common option
#define P_MOS_COM16    0b100001011000 //P-MOS open drain output and 16 common option

#define PWM_1          0b100101000000 //PWM 1/16 duty
#define PWM_2          0b100101000010 //PWM 2/16 duty
#define PWM_3          0b100101000100 //PWM 3/16 duty
#define PWM_4          0b100101000110 //PWM 4/16 duty
#define PWM_5          0b100101001000 //PWM 5/16 duty
#define PWM_6          0b100101001010 //PWM 6/16 duty
#define PWM_7          0b100101001100 //PWM 7/16 duty
#define PWM_8          0b100101001110 //PWM 8/16 duty
#define PWM_9          0b100101010000 //PWM 9/16 duty
#define PWM_10         0b100101010010 //PWM 10/16 duty
#define PWM_11         0b100101010100 //PWM 11/16 duty
#define PWM_12         0b100101010110 //PWM 12/16 duty
#define PWM_13         0b100101011000 //PWM 13/16 duty
#define PWM_14         0b100101011010 //PWM 14/16 duty
#define PWM_15         0b100101011100 //PWM 15/16 duty
#define PWM_16         0b100101011110 //PWM 16/16 duty

void InitHT1632C() {
  // initialisation de la matrice de led
  // apparement les broches OSC et SYNC des quatres HT1632C ne sont pas reliées dans cette matrice
  // on ne peut donc pas définir le premier HT1632c en MASTER et les suivants en SLAVE,
  // tous doivent être déclarés en mode master et utiliser le résonnateur interne (commande RC)

  SelectAll();                     // enable all HT1632Cs
  CommandWriteHT1632C(SYS_DIS);    // sends command
  SelectNone();                    // disable all HT1632Cs

  SelectAll();
  CommandWriteHT1632C(N_MOS_COM8);
  SelectNone();

  SelectAll();
  CommandWriteHT1632C(RC_MASTER_MODE);
  SelectNone();

  SelectAll();
  CommandWriteHT1632C(SYS_EN);
  SelectNone();

  SelectAll();
  CommandWriteHT1632C(PWM_10);
  SelectNone();

  SelectAll();
  CommandWriteHT1632C(LED_ON);
  SelectNone();

  SelectAll();
  DataClearHT1632C();
  SelectNone();
}

void SelectNone() {
  HT1632C_CLK_0;  // clock line is 0
  CLK_DELAY;

  HT1632C_CS_1; // send "1" to cs port
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°1
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°2
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°3
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°4
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CS_1; // send "1" to cs port
  CLK_DELAY;
}

void SelectAll() {
  HT1632C_CLK_0;  // clock line is 0
  CLK_DELAY;

  HT1632C_CS_0; // send "0" to cs port
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°1
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°2
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°3
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°4
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CS_1; // send "1" to cs port
  CLK_DELAY;
}

void SelectFirst() {
  HT1632C_CLK_0;  // clock line is 0
  CLK_DELAY;

  HT1632C_CS_0; // send "0" to cs port
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°1
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CS_1; // send "1" to cs port
  CLK_DELAY;
}

void SelectSecond() {
  HT1632C_CLK_0;  // clock line is 0
  CLK_DELAY;

  HT1632C_CS_0; // send "0" to cs port
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°1
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  HT1632C_CS_1; // send "1" to cs port
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°2
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

}


void CommandWriteHT1632C(unsigned int command) {
  unsigned int j;
  command = command & 0x0fff;   // 12-bit command word, mask upper four bits

  HT1632C_WR_0;  // clock line is 0
  CLK_DELAY;

  // write command words in HT1632C register :
  for (int i = 0; i < 12; i++) {
    j = command & 0x0800;        // return the MSB
    command = command << 1;      // move the control character to the left one
    j = j >> 11;                 // position the value at the LSB
    HT1632C_DATA(j);             // send the value to the data port
    CLK_DELAY;

    HT1632C_WR_1;  // clock pulse
    CLK_DELAY;
    HT1632C_WR_0;
    CLK_DELAY;
  }
}

void ColumnWriteHT1632C(uint8 address, uint8 data) {

  HT1632C_WR_0;  // clock line is 0
  CLK_DELAY;

  // operation = WRITE = send 101
  HT1632C_DATA_1; // send "1" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  HT1632C_DATA_0; // send "0" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  HT1632C_DATA_1; // send "1" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;


  // select address
  uint8 j;
  address = address & 0x7f;  // 7-bit command word, mask upper bit

  for (int i = 0; i < 7; i++) {
    j = address & 0x40;          // return the MSB
    address = address << 1;      // move the control character to the left one
    j = j >> 6;                  // position the value at the LSB
    HT1632C_DATA(j);             // send the value to the data port
    CLK_DELAY;

    HT1632C_WR_1;  // clock pulse
    CLK_DELAY;
    HT1632C_WR_0;
    CLK_DELAY;
  }

  // send data
  for (int i = 0; i < 8; i++) {
    j = data & 0x80;          // return the MSB
    data = data << 1;      // move the control character to the left one
    j = j >> 7;                  // position the value at the LSB
    HT1632C_DATA(j);             // send the value to the data port
    CLK_DELAY;

    HT1632C_WR_1;  // clock pulse
    CLK_DELAY;
    HT1632C_WR_0;
    CLK_DELAY;
  }
}

void ClearBufferHT1632(uint8 *bufferHT1632) {
  for (int i = 0 ; i < BUFFER_LENGHT ; i++) {
    bufferHT1632[i] = 0;
  }
}

void SetPixelHT1632(uint8 *bufferHT1632, int x, int y, int color) {
  int offset = -1;
  // dans quelle zone de l'écran se trouve le pixel ? quel HT1632 doit-on activer ?
  if (y >= 0 && y < 8) {
    if (x >= 0 && x < 16) {
      // HT1632 #1
      offset = 0;
    }
    else if (x >= 16 && x < 32) {
      // HT1632 #2
      offset = 1;
    }
  }
  else if (y >= 8 && y < 32) {
    if (x >= 0 && x < 16) {
      // HT1632 #3
      offset = 2;
    }
    else if (x >= 16 && x < 32) {
      // HT1632 #4
      offset = 3;
    }
  }
  // si x ou y ne sont pas dans les limites, on abandonne !
  if (offset == -1) {
    return;
  }
  x = x % 16;
  y = y % 8;
  int n = x + offset * 32;
  uint8 mask = (0x80 >> y);

  // green LEDs
  if (color == 1 || color == 3) {
    bufferHT1632[n] = bufferHT1632[n] | mask;
  }
  else {
    bufferHT1632[n] = bufferHT1632[n] & (~mask);
  }

  // red LEDs
  if (color == 2 || color == 3) {
    bufferHT1632[n + 16] = bufferHT1632[n + 16] | mask;
  }
  else {
    bufferHT1632[n + 16] = bufferHT1632[n + 16] & (~mask);
  }
}


void SetCharHT1632(uint8 *bufferHT1632, char c, int x, int y, int color) {
  int n = c - 32;
  int start = FONT_5X4_START[n];
  int width = FONT_5X4_START[n + 1] - FONT_5X4_START[n];
  for (int i = 0 ; i < width ; i++) {
    bufferHT1632[i] = pgm_read_byte_near(FONT_5X4 + start + i);
  }
  
  start = FONT_8X4_START[n];
  width = FONT_8X4_START[n + 1] - FONT_8X4_START[n];
  for (int i = 0 ; i < width ; i++) {
    bufferHT1632[i+8] = pgm_read_byte_near(FONT_8X4 + start + i);
  }
}



void ScrollLeftHT1632(uint8 *buffer0, uint8 *buffer1, int duration) {
  for (int offset = 1 ; offset < 32 ; offset ++) {
    ShiftLeftHT1632(buffer0, buffer1, bufferTemp, offset);
    RenderHT1632(bufferTemp);
    delay(duration / 32);
  }
}

void ScrollRightHT1632(uint8 *buffer0, uint8 *buffer1, int duration) {
  for (int offset = 1 ; offset < 32 ; offset ++) {
    ShiftRightHT1632(buffer0, buffer1, bufferTemp, offset);
    RenderHT1632(bufferTemp);
    delay(duration / 32);
  }
}


void ShiftRightHT1632(uint8 * buffer0, uint8 * buffer1, uint8 * buffer2, int offset) {
  ShiftLeftHT1632(buffer1, buffer0, buffer2, 32 - offset);
}


void ShiftLeftHT1632(uint8 * buffer0, uint8 * buffer1, uint8 * buffer2, int offset) {
  int n = 0;
  if (offset >= 0 && offset < 16) {
    // ligne 1
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer0[i + 32];
      n++;
    }
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 16];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer0[i + 48];
      n++;
    }

    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 32];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i];
      n++;
    }
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 48];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 16];
      n++;
    }

    // ligne 2
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 64];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer0[i + 32 + 64];
      n++;
    }
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 16 + 64];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer0[i + 48 + 64];
      n++;
    }

    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 32 + 64];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 64];
      n++;
    }
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 48 + 64];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 16 + 64];
      n++;
    }

  }
  else if (offset >= 16 && offset < 32) {
    offset = offset - 16;
    // ligne 1
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 32];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i];
      n++;
    }
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 48];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 16];
      n++;
    }

    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer1[i];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 32];
      n++;
    }
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer1[i + 16];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 48];
      n++;
    }

    // ligne 2
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 32 + 64];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 64];
      n++;
    }
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer0[i + 48 + 64];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 16 + 64];
      n++;
    }

    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer1[i + 64];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 32 + 64];
      n++;
    }
    for (int i = offset ; i < 16 ; i++) {
      buffer2[n] = buffer1[i + 16 + 64];
      n++;
    }
    for (int i = 0 ; i < offset ; i++) {
      buffer2[n] = buffer1[i + 48 + 64];
      n++;
    }
  }
}



void RenderHT1632(uint8 * bufferHT1632) {
  // on active un a un les HT1632

  HT1632C_CLK_0;  // clock line is 0
  CLK_DELAY;

  HT1632C_CS_0; // send "0" to cs port
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°1
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  // HT1632 #1 actif

  DataWriteHT1632C(bufferHT1632);


  HT1632C_CS_1; // send "1" to cs port
  CLK_DELAY;

  HT1632C_CLK_1;  // clock pulse n°2
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  // HT1632 #1 inactif
  // HT1632 #2 actif

  DataWriteHT1632C(bufferHT1632 + 32);


  HT1632C_CLK_1;  // clock pulse n°3
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  // HT1632 #2 inactif
  // HT1632 #3 actif

  DataWriteHT1632C(bufferHT1632 + 64);


  HT1632C_CLK_1;  // clock pulse n°4
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  // HT1632 #3 inactif
  // HT1632 #4 actif

  DataWriteHT1632C(bufferHT1632 + 96);


  HT1632C_CLK_1;  // clock pulse n°5
  CLK_DELAY;
  HT1632C_CLK_0;
  CLK_DELAY;

  // HT1632 #4 inactif
}





void DataWriteHT1632C(uint8 * bufferHT1632) {
  // pour un HT1632C, soit deux matrice 8x8 bicolores :
  // on selectionne la première adresse 0x00
  // en envoyant la séquence 1010000000
  // puis on envoie les 32 octects

  HT1632C_WR_0;  // clock line is 0
  CLK_DELAY;

  HT1632C_DATA_1; // send "1" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  HT1632C_DATA_0; // send "0" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  HT1632C_DATA_1; // send "1" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  for (int i = 0; i < 7; i++) {
    HT1632C_DATA_0; // send "0" to data port
    CLK_DELAY;

    HT1632C_WR_1;  // clock pulse
    CLK_DELAY;
    HT1632C_WR_0;
    CLK_DELAY;
  }

  uint8 data = 0b00000000;
  int k;
  for (int i = 0; i < 32; i++) {
    data = bufferHT1632[i];
    for (int j = 0; j < 8; j++) {
      k = data & 0x80;          // return the MSB
      data = data << 1;      // move the control character to the left one
      k = k >> 7;                  // position the value at the LSB
      HT1632C_DATA(k);             // send the value to the data port
      CLK_DELAY;

      HT1632C_WR_1;  // clock pulse
      CLK_DELAY;
      HT1632C_WR_0;
      CLK_DELAY;
    }
  }
}




/*
  void DataWriteHT1632C() {
  // pour un HT1632C, soit deux matrice 8x8 bicolores :
  // on selectionne la première adresse 0x00
  // en envoyant la séquence 1010000000

  HT1632C_WR_0;  // clock line is 0
  CLK_DELAY;

  HT1632C_DATA_1; // send "1" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  HT1632C_DATA_0; // send "0" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  HT1632C_DATA_1; // send "1" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  for (int i = 0; i < 7; i++) {
    HT1632C_DATA_0; // send "0" to data port
    CLK_DELAY;

    HT1632C_WR_1;  // clock pulse
    CLK_DELAY;
    HT1632C_WR_0;
    CLK_DELAY;
  }

  // en envoie ensuite les 16 octets correspondants aux 16 colonnes de 8 leds vertes

  for (int j = 0; j < 8 ; j++) {
    HT1632C_DATA_1; // send "1" to data port
    CLK_DELAY;

    HT1632C_WR_1;  // clock pulse
    CLK_DELAY;
    HT1632C_WR_0;
    CLK_DELAY;
  }

  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 8 ; j++) {
      HT1632C_DATA_0; // send "0" to data port
      CLK_DELAY;

      HT1632C_WR_1;  // clock pulse
      CLK_DELAY;
      HT1632C_WR_0;
      CLK_DELAY;
    }
  }

  // en envoie ensuite les 16 octets correspondants aux 16 colonnes de 8 leds rouges

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 8 ; j++) {
      HT1632C_DATA_0; // send "0" to data port
      CLK_DELAY;

      HT1632C_WR_1;  // clock pulse
      CLK_DELAY;
      HT1632C_WR_0;
      CLK_DELAY;
    }
  }

  }
*/
void DataClearHT1632C() {
  // pour un HT1632C, soit deux matrice 8x8 bicolores :
  // on selectionne la première adresse 0x00
  // en envoyant la séquence 1010000000

  HT1632C_WR_0;  // clock line is 0
  CLK_DELAY;

  HT1632C_DATA_1; // send "1" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  HT1632C_DATA_0; // send "0" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  HT1632C_DATA_1; // send "1" to data port
  CLK_DELAY;

  HT1632C_WR_1;  // clock pulse
  CLK_DELAY;
  HT1632C_WR_0;
  CLK_DELAY;

  for (int i = 0; i < 7; i++) {
    HT1632C_DATA_0; // send "0" to data port
    CLK_DELAY;

    HT1632C_WR_1;  // clock pulse
    CLK_DELAY;
    HT1632C_WR_0;
    CLK_DELAY;
  }

  // en envoie ensuite les 32 octets correspondants aux 16 colonnes de 8 leds vertes ....

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 8 ; j++) {
      HT1632C_DATA_0; // send "0" to data port
      CLK_DELAY;

      HT1632C_WR_1;  // clock pulse
      CLK_DELAY;
      HT1632C_WR_0;
      CLK_DELAY;
    }
  }
}


