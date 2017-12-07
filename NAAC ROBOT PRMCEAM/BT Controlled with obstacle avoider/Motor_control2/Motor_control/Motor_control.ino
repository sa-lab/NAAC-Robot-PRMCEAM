 #include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#define echopin  8
#define trigpin 2
int maximumRange = 30;
long duration, distance;
SoftwareSerial BT(0, 1);  //TX, RX pins 
String readdata;
int m1 = 3, m2 = 4, m3 = 5, m4 = 7;
int x;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

void setup() {  // setup function for pins mode
  lcd.begin(16, 2);
  pinMode (trigpin, OUTPUT);   //sets the trig pin of sensor for o/p
  pinMode (echopin, INPUT );
  BT.begin(9600); 
  Serial.begin(9600);  
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("PRMCEAM Welcomes");
  lcd.setCursor(0, 1);
  lcd.print("NAAC TEAM");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Bot Designed by ");
  lcd.setCursor(0, 1);

  lcd.print(" Sujay Alaspure ");
  delay(3000);
  lcd.clear();
}
// this function will be executed again again //
void loop() {
   {
    digitalWrite(trigpin, LOW); 
    delayMicroseconds(2); 

    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10); 

    duration = pulseIn (echopin, HIGH);

    distance = duration / 48.2; 
    delay (40);// delay of 40 millis
  }
    lcd.setCursor(0,0);
        lcd.print("distance=");
    lcd.print(distance);//taking the distance
        lcd.print("cm     ");
  while (BT.available()) {   
    delay(10);   
    char c = BT.read();  
    readdata += c;   
  }
  if (readdata.length() > 0) {
    Serial.println(readdata);
    if (readdata == "forward" || readdata == "FF")  //from BT for forward motion
    {
      lcd.setCursor(0, 1);
      lcd.print("Forward         ");
 {
    digitalWrite(trigpin, LOW); 
    delayMicroseconds(2); 

    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10); 

    duration = pulseIn (echopin, HIGH);

    distance = duration / 48.2; 
    delay (40);// delay of 40 millis
 
  }
      if (distance >= 30 ){
    digitalWrite(3,HIGH); 
    digitalWrite(4,0);
    digitalWrite(5,1);
    digitalWrite(7,LOW);
//    delay (200);
  }
  
  else if (distance >=14 && distance <= 24) {
    digitalWrite (3,HIGH);
    digitalWrite (4,LOW);
    digitalWrite (5,LOW);
    digitalWrite (7,LOW);
    delay (1000);
  }
 else if (distance < 14){ 
   digitalWrite (3, LOW);
   digitalWrite (4, 1);
   digitalWrite (5,0);
   digitalWrite (7,HIGH);
   delay (1000); // take a delay of 1 second

   digitalWrite (3,LOW);
   digitalWrite (4,HIGH);
   digitalWrite (5,LOW);
   digitalWrite (7, LOW);
   delay (1000);  
 }

//      digitalWrite(m1, HIGH);
//      digitalWrite (m2, 0);
//      digitalWrite(m3, 1);
//      digitalWrite(m4, LOW);
//      delay(100);
    }

    else if (readdata == "reverse" || readdata == "BB") //for reverse motion

    {
      lcd.setCursor(0, 1);
      lcd.print("Backward         ");
      digitalWrite(m1, LOW);
      digitalWrite(m2, 1);
      digitalWrite(m3, 0);
      digitalWrite(m4, HIGH);
      delay(100);
    }
    else if (readdata == "right" || readdata == "RR")    //for turning right
    {
      lcd.setCursor(0, 1);
      lcd.print("Right         ");
      digitalWrite (m1, HIGH);
      digitalWrite (m2, 0);
      digitalWrite (m3, LOW);
      digitalWrite (m4, LOW);
      delay (100);
    }
    else if ( readdata == "left" || readdata == "LL")  //for turning left
    {
      lcd.setCursor(0, 1);
      lcd.print("Left         ");
      digitalWrite (m1, 0);
      digitalWrite (m2, 0);
      digitalWrite (m3, 1);
      digitalWrite (m4, LOW);
      delay (100);
    }
    else if (readdata == "stop" || readdata == "SS")  // to stop the robo
    {
      lcd.setCursor(0, 1);
      lcd.print("Stoped......     ");
      digitalWrite (m1, LOW);
      digitalWrite (m2, LOW);
      digitalWrite (m3, LOW);
      digitalWrite (m4, LOW);
      delay (100);
    }
    readdata = "";
  }
} //Reset the variable

