// This is the best I can do for the code without testing on motor and having the encoder 
#include <Encoder.h> // have to install encoder library see instructions on handout
#include <Wire.h>
#define SLAVE_ADDRESS 0x04
double prePos = 0;
double preTime = 0;
double angVel = 0;
double micTime = 0;
Encoder knobLeft(2, 5);
Encoder knobRight(7, 8);
void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(12, INPUT);
  Serial.begin(38400);
  Wire.begin(SLAVE_ADDRESS);
  delay(1000);
}
long postitionLeft =-999;
long positionRight = -999;
long leftAng = 0;

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(9, 64);
  digitalWrite(7, HIGH); // Or what ever speed we want robot to go
  if ((millis() < 2000) && (millis() > 1000)) {
    
    //OUTPUT MOTOR ANGULAR VELOCITY AND POSITION
    long newLeft; // new postion
    newLeft=knobLeft.read() % 3200; // mod so that output is between 0 and 2 pi
    double leftAng =  (double)newLeft * 6.28 / 3200; // calulation of angular position
    //Serial.print("Wheel positon = "); // print 
    micTime = micros()/1000000;
    Serial.print(micTime);
    Serial.print(",");
    Serial.print(leftAng);
    Serial.print(",");
    angVel = (leftAng - prePos)/(micTime - preTime);
    Serial.print(angVel);
    prePos = leftAng;
    preTime = micTime;
    Serial.println();
    postitionLeft=newLeft; // position counter equals new position counter
    
     // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
    
  }
  delay(5)
}
