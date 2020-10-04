// This is the best I can do for the code without testing on motor and having the encoder 
#include <Encoder.h> // have to install encoder library see instructions on handout
Encoder knobLeft(2, 5);
Encoder knobRight(7, 8);
double Kp = 3.61902322209485;
double Ki = 1.11609397897048;
//double Kd = 0.569618462570328;
double Kd = 3;
double r = 1;
double time1 = 0;
double time2 = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(12, INPUT);
  Serial.begin(250000); // FIX FIX FIX FIX FIX 
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
double umax = 127;

void loop() {
   time1 = micros();
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
  Serial.print("P : ");
  Serial.print(leftAng);
  Serial.println();
  time2 = micros();
  //Serial.print(time2-time1);

   double e = r - leftAng; // Error in rad
   Serial.print("e : ");
   Serial.print(e);
   Serial.println();
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
     e = signbit(e)*min(umax / Kp, abs(e));
     I = (u-Kp*e-Kd*D)/Ki;
   }
   u = 127 - abs(u);
   Serial.print("U : ");
   Serial.print(u);
   Serial.println();
   Serial.print("Sign : ");
   Serial.print(signbit(-1*e));
   Serial.println();
   analogWrite(9, abs(u));
   digitalWrite(7, signbit(-1*e));
   Ts = millis() - Tc;
   Tc = millis();
   delay(18);
    
}
