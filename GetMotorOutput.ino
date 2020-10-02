// This is the best I can do for the code without testing on motor and having the encoder 

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(12, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(9, 0);

  digitalWrite(7, LOW);
  if (millis() < 2000) & (millis() > 1000) {
    analogWrite(9, 225) // Turn on whatever speed we want our robot to go
    //OUTPUT MOTOR ANGULAR VELOCITY AND POSITION
    
  }
}
