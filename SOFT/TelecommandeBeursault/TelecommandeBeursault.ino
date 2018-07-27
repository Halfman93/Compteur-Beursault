#include <VirtualWire.h>

byte btn0 = 5;
byte btn1 = 6;
byte btn2 = 7;
byte btn3 = 8;
byte btn4 = 9;
byte btnNo = 10;
byte led = 12;

void setup()
{
  pinMode(btn0, INPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btnNo, INPUT);

  pinMode(led, OUTPUT);

  Serial.begin(9600);

  vw_set_tx_pin(3);
  vw_setup(2000); // initialisation de la bibliothèque VirtualWire à 2000 bauds
  
}

void Send(int value)
{
  Serial.println(value); 
  digitalWrite(led,HIGH);
  byte message[2];
  memcpy(message, &value, sizeof(value));
  vw_send(message,2);
  vw_wait_tx();
  delay(400);
  digitalWrite(led,LOW);
  
}
void loop() 
{
   if(digitalRead(btn0) == HIGH)
    {
      Send(0);
    }
    if(digitalRead(btn1) == HIGH)
    {
      Send(1);
    }
    if(digitalRead(btn2) == HIGH)
    {
      Send(2);
    }
    if(digitalRead(btn3) == HIGH)
    {
      Send(3);
    }
    if(digitalRead(btn4) == HIGH)
    {
      Send(4);
    }
    if(digitalRead(btnNo) == HIGH)
    {
      Send(5);
    }

}
