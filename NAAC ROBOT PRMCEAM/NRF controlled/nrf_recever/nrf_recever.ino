
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE   9
#define CSN 10
int FWD; int BWD;  int LEFT; int RIGHT; int MODE; int SW; int VRx; int VRy;     // nRF variables
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE, CSN);
int data[9];
int R1 = 3, R2 = 4, L1 = 5, L2 = 7, en = 6;
int SPEED;
void setup() {
  // put your setup code here, to run once:
  radio.begin();
  Serial.begin(9600);
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(en, OUTPUT);

}

void loop() {
  if ( radio.available() )
  {
    radio.read( data , sizeof(data) );
    nRF(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);
  }//else lcd.print("Radio not Available");}


}
void nRF(int FWD, int BWD,  int LEFT, int RIGHT, int MODE, int SW, int VRx, int VRy, int SPEED) {

  Serial.print(FWD);
  Serial.print(BWD);
  Serial.print(LEFT);
  Serial.print(RIGHT);
  Serial.print(MODE);
  Serial.print(SW);
  Serial.print(VRx);
  Serial.print(VRy);
  Serial.println(SPEED);
  if (FWD == 1) {                                            //Forward
    digitalWrite(R1, 1);
    digitalWrite(R2, 0);
    digitalWrite(L1, 1);
    digitalWrite(L2, 0);
    digitalWrite(en, 1);
  } else if (BWD == 1) {                                     //Backward
  digitalWrite(R1, 0);
    digitalWrite(R2, 1);
    digitalWrite(L1, 0);
    digitalWrite(L2, 1);
    digitalWrite(en, 1);
  } else if (RIGHT == 1) {                                    //Left
    digitalWrite(R1, 1);
    digitalWrite(R2, 0);
    digitalWrite(L1, 0);
    digitalWrite(L2, 0);
    digitalWrite(en, 1);
  } else if (LEFT == 1) {                                     //Right
    digitalWrite(R1, 0);
    digitalWrite(R2, 0);
    digitalWrite(L1, 1);
    digitalWrite(L2, 0);
    digitalWrite(en, 1);
  } else {
    digitalWrite(R1, 0);
    digitalWrite(R2, 0);
    digitalWrite(L1, 0);
    digitalWrite(L2, 0);
  }

    if (VRx > 525) {                                            //Forward
    digitalWrite(R1, 1);
    digitalWrite(R2, 0);
    digitalWrite(L1, 1);
    digitalWrite(L2, 0);
    analogWrite(en, SPEED);
  } if (VRx<460) {                                     //Backward
    digitalWrite(R1, 0);
    digitalWrite(R2, 1);
    digitalWrite(L1, 0);
    digitalWrite(L2, 1);
    analogWrite(en, SPEED);
  } if (VRy<460) {                                    //Left
    digitalWrite(R1, 0);
    digitalWrite(R2, 0);
    digitalWrite(L1, 1);
    digitalWrite(L2, 0);
    analogWrite(en, SPEED);
  } 
  if (VRy>525) {                                     //Right
    digitalWrite(R1, 1);
    digitalWrite(R2, 0);
    digitalWrite(L1, 0);
    digitalWrite(L2, 0);
    analogWrite(en, SPEED);
  }

}
