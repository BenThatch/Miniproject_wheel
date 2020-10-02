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
  Serial.begin(250000);
  digitalWrite(7, LOW);
  analogWrite(9, 0);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, LOW);
  analogWrite(9, 127); // Or what ever speed we want robot to go
  if (millis() < 2000) & (millis() > 1000) {
    
    //OUTPUT MOTOR ANGULAR VELOCITY AND POSITION
    
  }
}
