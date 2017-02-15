
/*
 * ce sketch permet de tester la matrice RGB 32x16 de Adafruit avec un esp8266
 * 
 * afin d'économiser les broches de l'esp, on n'envoie les données que dans les broches R1, G1 et B1.
 * en bouclant les sorties R1, G1 et B1 sur les entrées R2, G2, B2 on simule deux matrices 32x8 en série
 */

// définition des pins
int latchPin = 16;         // D0 = GPIO16
int clockPin = 2;          // D4 = GPIO2
int outputEnablePin = 0;   // D3 = GPIO0

int APin = 12;             // D6 = GPIO12
int BPin = 5;              // D1 = GPIO5
int CPin = 14;             // D5 = GPIO14

int R1Pin = 15;            // D8 = GPIO15
int G1Pin = 4;             // D2 = GPIO4
int B1Pin = 13;            // D7 = GPIO13

// variables nécessaires à la selection des lignes de la matrice
int a;
int b;
int c;

// pour régler l'intensité des leds, on joue sur la durée d'allumage / d'extinction
int intensite = 50; // entre 0 et 100

// une variable uint32_t permet de stocker 32 bits, soit un bit par leds d'une ligne monochromatique
// 48 uint32_t couvrent donc les 16 lignes de 3 couleurs
//
// tampon[0] contient l'information necessaire pour allumer les leds ROUGES de la PREMIERE ligne
// tampon[1] contient l'information necessaire pour allumer les leds VERTES de la PREMIERE ligne
// tampon[2] contient l'information necessaire pour allumer les leds BLEUES de la PREMIERE ligne
//
// tampon[3] contient l'information necessaire pour allumer les leds ROUGES de la DEUXIEME ligne
// etc.

uint32_t tampon[48];

// variable utilisée comme masque lors du transfert
uint32_t one = 1;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(outputEnablePin, OUTPUT);

  pinMode(APin, OUTPUT);
  pinMode(BPin, OUTPUT);
  pinMode(CPin, OUTPUT);

  pinMode(R1Pin, OUTPUT);
  pinMode(G1Pin, OUTPUT);
  pinMode(B1Pin, OUTPUT);

  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(outputEnablePin, LOW);

  digitalWrite(APin, LOW);
  digitalWrite(BPin, LOW);
  digitalWrite(CPin, HIGH);

  digitalWrite(R1Pin, LOW);
  digitalWrite(G1Pin, LOW);
  digitalWrite(B1Pin, LOW);

  // on éteint toutes les leds par défaut
  for (int i = 0; i < 8; i++) {
    tampon[i] = 0;
  }

  // un texte d'exemple
  tampon[0] = 7246225;

  tampon[4] = 2402985;

  tampon[8] = 6597033;

  tampon[9] = 2403001;
  tampon[10] = 2403001;

  tampon[12] = 6590891;
  tampon[14] = 6590891;

  tampon[25] = 7246225;
  tampon[26] = 7246225;

  tampon[27] = 2402985;
  tampon[28] = 2402985;
  tampon[29] = 2402985;

  tampon[30] = 6597033;
  tampon[34] = 2403001;
  tampon[38] = 6590891;
}

void loop() {

  for (int i = 0; i < 8; i++) {

    // on eteint les led
    digitalWrite(outputEnablePin, HIGH);

    // on active la ligne i.
    a = (i & 0x0001);
    b = (i & 0x0002) >> 1;
    c = (i & 0x0004) >> 2;

    digitalWrite(APin, a);
    digitalWrite(BPin, b);
    digitalWrite(CPin, c);

    // on envoie les données
    // d'abord les lignes du bas de l'afficheur
    for (int j=0; j<32; j++) {
      // on envoie la ligne tampon[3*i+24] dans R1 (ligne i + 8)
      digitalWrite(R1Pin, (tampon[3*i+24] >> j) & one);
      
      // on envoie la ligne tampon[3*i+24+1] dans G1 (ligne i + 8)
      digitalWrite(G1Pin, (tampon[3*i+24+1] >> j) & one);
      
      // on envoie la ligne tampon[3*i+24+2] dans B1 (ligne i + 8)
      digitalWrite(B1Pin, (tampon[3*i+24+2] >> j) & one);

      // tic tac
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
    }

    // puis les lignes du haut
    for (int j=0; j<32; j++) {
      // on envoie la ligne tampon[3*i] dans R1 (ligne i)
      digitalWrite(R1Pin, (tampon[3*i] >> j) & one);
      
      // on envoie la ligne tampon[3*i+1] dans G1 (ligne i)
      digitalWrite(G1Pin, (tampon[3*i+1] >> j) & one);
      
      // on envoie la ligne tampon[3*i+2] dans B1 (ligne i)
      digitalWrite(B1Pin, (tampon[3*i+2] >> j) & one);

      // tic tac
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
    }

    // lach
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);

    // on laisse les leds éteintes quelques microsecondes pour moduler l'intensité
    delayMicroseconds(100 - intensite);

    // on allume les leds
    digitalWrite(outputEnablePin, LOW);

    // on laisse les leds allumées quelques microsecondes et c'est reparti !
    delayMicroseconds(intensite);

  }
}
