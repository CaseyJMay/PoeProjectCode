#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor = AFMS.getMotor(1); // Right Motor

char motorSpeed;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    motorSpeed = Serial.readString().toInt();
    motor->setSpeed(motorSpeed);
  }
  else {
    motor->setSpeed(0);
    }
}
