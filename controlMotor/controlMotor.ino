// QUESTIONS:
// 1. Serial.available is always 0
// 2. readstring is not properly working


#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor = AFMS.getMotor(2);

char motorSpeed;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  Serial.print("Ready");
}

void loop() {
  Serial.print(" || Serial Value: ");
  Serial.print(Serial.available());

  while (Serial.available() >= 0) {
    motorSpeed = Serial.read();
    Serial.print("| Motorspeed: ");
    Serial.print(motorSpeed);
    
    if (motorSpeed == 1) {
      motor->setSpeed(80);
      Serial.print("| motor fast");
//      motor->run(FORWARD);
    }
    else if (motorSpeed == 0) {
      motor->setSpeed(40);
      Serial.print("| motor slow");
//      motor->run(FORWARD);
    }
    else {
      motor->setSpeed(20);
      Serial.print("| nothing?");
//      motor->run(FORWARD);
    }
    motor->run(FORWARD);
  }
  delay(2);
  Serial.println("out of while");
}
