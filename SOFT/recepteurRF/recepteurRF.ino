#include <VirtualWire.h>

byte I0 = 2;
byte I1 = 3;
byte I2 = 4;
byte I3 = 5;
byte I4 = 6;


void setup() {
  Serial.begin(9600);

  pinMode(I0, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);
    
  vw_set_rx_pin(12);
  vw_set_tx_pin(11);
  vw_setup(2000);
  vw_rx_start(); // On peut maintenant recevoir des messages

  Serial.println("Go !"); 
}

void loop() {
  byte message[2];
  byte taille_message = 2;
  int valeur;

  if (vw_get_message(message, &taille_message)) {
    // On copie le message, qu'il soit corrompu ou non

    memcpy(&valeur, message, sizeof(valeur));
    Serial.println(valeur); // Affiche le message
    switch(valeur)
    {
      case 0 : digitalWrite(I0,HIGH);
               delay(1000);
               digitalWrite(I0,LOW);
               break;
      case 1 : digitalWrite(I1,HIGH);
               delay(1000);
               digitalWrite(I1,LOW);
               break;
      case 2 : digitalWrite(I2,HIGH);
               delay(1000);
               digitalWrite(I2,LOW);
               break;
      case 3 : digitalWrite(I3,HIGH);
               delay(1000);
               digitalWrite(I3,LOW);
               break;
      case 4 : digitalWrite(I4,HIGH);
               delay(1000);
               digitalWrite(I4,LOW);
               break;
      case 5 : digitalWrite(I0,HIGH);
               digitalWrite(I1,HIGH);
               delay(1000);
               digitalWrite(I0,LOW);
               digitalWrite(I1,LOW);
               break;
    }
  }

}

