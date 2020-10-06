// This is the best I can do for the code without testing on motor and having the encoder 
#include <Encoder.h> // have to install encoder library see instructions on handout
Encoder knobLeft(2, 5);
Encoder knobRight(7, 8);
double Kp = 3;     //4.04279756570629;  //1902322209485; // This value works
//double Kp = 1.743511643388056;  // This value works
//double Kp = 1;
//double Ki = 0;   //609397897048;
double Ki = 0.13; //31442; //08562799;
//double Kd = 0.569618462570328;
double Kd = 1;
double r = -1;
double angVel = 0;
double prePos = 0;
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
  delay(1000);
}

long postitionLeft =-999;
//long positionRight = -999;
long leftAng = 0;
double I = 0;
double D = 0;
double ePast = 0;
double Ts = 0;
double Tc = millis();
double u = 0;
double i = 0;
double umax = 7.2;

void loop() {
   //time1 = micros();
   long newLeft; // new postion
   newLeft=knobLeft.read(); //% 3200; // mod so that output is between 0 and 2 pi
   double leftAng =  (double)newLeft * 6.28 / 3200; // calulation of angular position

    // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
    Serial.print(micros());
    Serial.print(",");
    Serial.print(leftAng);
    Serial.print(",");
    angVel = 1000*(leftAng - (1.00 - ePast))/Ts;
    Serial.print(angVel);
    Serial.println();

   double e = r - leftAng; // Error in rad
   if (abs(e) <= 0.02) {
    Ki = 0.3;
   }
   if (Ts > 0) {
     D = (e - ePast)/Ts; // rad/sec Derivative 
     ePast = e;
   }
   else {
     D = 0; // rad/sec
   }
   I = I + Ts*e; // Rad*s
   u = Kp*e + Ki*I + Kd*D; // (V/rad) * rad + (V/rad*sec) * (rad/sec) + (V/(rad/sec)) * (rad/sec)
   // Final Units from above is only V
   if (abs(u) > umax) {
    //u = umax;
     u = signbit(u)*umax;
     I = (u-Kp*e-Kd*D)/Ki;
   }
  // u = umax - u;
  if (abs(e) == 0) {
    u = 0;
   }

   Serial.print(u);
   Serial.println();
   i = (u / umax) * 255;
   Serial.print(i);
   Serial.println();

   analogWrite(9, abs(i));
   digitalWrite(7, signbit(-1*e));
   Ts = millis() - Tc;
   Tc = millis();
   delay(25);
    
}
