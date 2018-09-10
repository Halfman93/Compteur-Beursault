//GPIO declarations
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
byte segmentClock = 6;
byte segmentLatch = 5;
byte segmentData = 7;

byte btn0 = 8;
byte btn1 = 9;
byte btn2 = 10;
byte btn3 = 11;
byte btn4 = 12;
byte btnBuzz = 4;

byte buzzer = A0;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int currentScore = 9;
unsigned long time = 0;
#define MAX_TIME_AFFICHE 5*1000 

void buzz(int nb)
{
  if(digitalRead(btnBuzz) == HIGH)
  {
    for(int i=0;i<nb;i++)
    {
      digitalWrite(buzzer,HIGH);
      delay(500);
      digitalWrite(buzzer,LOW);
      delay(500);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Large Digit Driver Example");

  pinMode(segmentClock, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);

  pinMode(btn0, INPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btnBuzz, INPUT);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);

  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);

  for(int i=4;i>=0;i--)
  {
    postNumber(i, false);
    digitalWrite(segmentLatch, LOW);
    digitalWrite(segmentLatch, HIGH); //Register moves storage register on the rising edge of RCK
    delay(500);
  }
   /* if(x == 0)
      postNumber(x, true); //Show decimal
    else
      postNumber(x, false);
      
    digitalWrite(segmentLatch, LOW);
    digitalWrite(segmentLatch, HIGH); //Register moves storage register on the rising edge of RCK
    delay(1000);
    
    x++;
    x %= 5; //Reset x after 9
    
    Serial.println(x); //For debugging
    */
}

byte doute = 0;
    
void loop()
{
    byte ispressed = 0;
    byte needBuzz = 0;

    if(digitalRead(btn0) == HIGH)
    {
      Serial.println(0);
      time = millis();
      currentScore = 0;
      needBuzz = 1;
      ispressed = 1;
    }
    if(digitalRead(btn1) == HIGH)
    {
      Serial.println(1);
      time = millis();
      currentScore = 1;
      needBuzz = 1;      
      if(ispressed == 1)
      {
        doute = 1;        
      }      
      ispressed = 1;
    }      
    if(digitalRead(btn2) == HIGH)
    {
      Serial.println(2);
      time = millis();
      currentScore = 2;
      needBuzz = 1;      
      if(ispressed == 1)
      {
        doute = 1;
      }
      ispressed = 1;
    }
    if(digitalRead(btn3) == HIGH)
    {
      Serial.println(3);
      time = millis();
      currentScore = 3;
      needBuzz = 1;     
      if(ispressed == 1)
      {
        doute = 1;
      }
       ispressed = 1;
    }
    if(digitalRead(btn4) == HIGH)
    {
      Serial.println(4);
      time = millis();
      currentScore = 4;
      needBuzz = 1;     
      if(ispressed == 1)
      {
        doute = 1;
      }
      ispressed = 1;
    }

    if(millis() < time+MAX_TIME_AFFICHE)
    {
      if(currentScore <=4)
      {
            if(doute == 1)
              postNumber('-', false);
            else
              postNumber(currentScore, false);
      }
    }
    else
    {
       Serial.println("TimeMax");
       for (byte x = 0 ; x < 8 ; x++)
       {
          digitalWrite(segmentClock, LOW);
          digitalWrite(segmentData, 0);
          digitalWrite(segmentClock, HIGH); //Data transfers to the register on the rising edge of SRCK
       }
       doute = 0;
    }
    digitalWrite(segmentLatch, LOW);
    digitalWrite(segmentLatch, HIGH); //Register moves storage register on the rising edge of RCK

    if(needBuzz == 1)
    {
      buzz(currentScore);
      needBuzz = 0;
    }
    
    delay(10);
}

//Takes a number and displays 2 numbers. Displays absolute value (no negatives)
void showNumber(float value)
{
  int number = abs(value); //Remove negative signs and any decimals

  //Serial.print("number: ");
  //Serial.println(number);

  for (byte x = 0 ; x < 2 ; x++)
  {
    int remainder = number % 10;

    postNumber(remainder, false);

    number /= 10;
  }

  //Latch the current segment data
  digitalWrite(segmentLatch, LOW);
  digitalWrite(segmentLatch, HIGH); //Register moves storage register on the rising edge of RCK
}

//Given a number, or '-', shifts it out to the display
void postNumber(byte number, boolean decimal)
{
  //    -  A
  //   / / F/B
  //    -  G
  //   / / E/C
  //    -. D/DP

#define a  1<<0
#define b  1<<6
#define c  1<<5
#define d  1<<4
#define e  1<<3
#define f  1<<1
#define g  1<<2
#define dp 1<<7

  byte segments;

  switch (number)
  {
    case 1: segments = b | c; break;
    case 2: segments = a | b | d | e | g; break;
    case 3: segments = a | b | c | d | g; break;
    case 4: segments = f | g | b | c; break;
    case 5: segments = a | f | g | c | d; break;
    case 6: segments = a | f | g | e | c | d; break;
    case 7: segments = a | b | c; break;
    case 8: segments = a | b | c | d | e | f | g; break;
    case 9: segments = a | b | c | d | f | g; break;
    case 0: segments = a | b | c | d | e | f; break;
    case ' ': segments = 0; break;
    case 'c': segments = g | e | d; break;
    case '-': segments = g; break;
  }

  if (decimal) segments |= dp;

  //Clock these bits out to the drivers
  for (byte x = 0 ; x < 8 ; x++)
  {
    digitalWrite(segmentClock, LOW);
    digitalWrite(segmentData, segments & 1 << (7 - x));
    digitalWrite(segmentClock, HIGH); //Data transfers to the register on the rising edge of SRCK
  }
}


