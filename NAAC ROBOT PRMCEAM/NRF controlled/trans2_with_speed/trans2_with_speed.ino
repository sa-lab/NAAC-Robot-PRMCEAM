
#include <SPI.h> 
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN 8
int FWD=A3;
int BWD=A0;
int LEFT=A1;
int RIGHT=A4;
int MODE=A2;
int SW=A5;
int VRx=A6, VRy=A7;
int MotorSpeed = 0;
int potpos = 512;
const uint64_t pipe = 0xE8E8F0F0E1LL; 
RF24 radio(CE_PIN, CSN_PIN); 
int data[9];  

void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  pinMode(FWD, INPUT);
  pinMode(BWD, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(MODE, INPUT);
  pinMode(SW, INPUT);
}

void loop()   
{

  data[0] = digitalRead(FWD);
  data[1] = digitalRead(BWD);
  data[2] = digitalRead(LEFT);
  data[3] = digitalRead(RIGHT);
  data[4] = digitalRead(MODE);
  data[5] = digitalRead(SW);
  data[6] = analogRead(VRx);

  data[7] = analogRead(VRy);
  data[8] = MotorSpeed;
  radio.write( data, sizeof(data) ); 

 potpos = analogRead(VRx);
 if (potpos < 460)
  {
    potpos = potpos - 460;                         // This produces a negative number
    potpos = potpos * -1;                          // Make the number positive
    potpos = map(potpos, 0, 460, 0, 255);
    MotorSpeed =potpos;
    if (MotorSpeed > 255)MotorSpeed = 255;
  }
  else if (potpos > 564)
  {
    potpos = map(potpos, 564, 1023, 0, 255);
    MotorSpeed =potpos;
    if (MotorSpeed < 0)MotorSpeed = 0;
  }else MotorSpeed = 0; 
  if (MotorSpeed < 8)MotorSpeed = 0;
Serial.println(MotorSpeed);
}
