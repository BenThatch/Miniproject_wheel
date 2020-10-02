// This is the best I can do for the code without testing on motor and having the encoder 
#include <Encoder.h> // have to install encoder library see instructions on handout

Encoder knobLeft(2, 5);
void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(12, INPUT);
  Serial.begin(250000);
  digitalWrite(7, LOW);
  analogWrite(9, 0);
  delay(1000);
}

long postitionLeft =-999;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, LOW);
  analogWrite(9, 127); // Or what ever speed we want robot to go
  if (millis() < 2000) & (millis() > 1000) {
    
    //OUTPUT MOTOR ANGULAR VELOCITY AND POSITION
    long newLeft; // new postion
    newLeft=knobLeft.read() % 3200; // mod so that output is between 0 and 2 pi
    double leftAng =  (double)newLeft * 6.28 / 3200; // calulation of angular position
    Serial.print("Wheel positon = "); // print 
    Serial.print(leftAng);
    Serial.println();
    positionLeft=newLeft; // position counter equals new position counter
    
     // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
    
  }
}
