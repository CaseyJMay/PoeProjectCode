#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor = AFMS.getMotor(2);

String motorSpeedStr;
int motorSpeed;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
}

void loop() {
//  Serial.print(" || Serial Value: ");
//  Serial.print(Serial.available());
  
  while (Serial.available() > 0) {
    motorSpeedStr = Serial.readString();
    Serial.print("| Motorspeed: ");
    Serial.print(motorSpeedStr);
    motorSpeed = atoi(motorSpeedStr.c_str());

    motor->setSpeed(motorSpeed);
    motor->run(FORWARD);
    
//    if (motorSpeed == "1") {
//      motor->setSpeed(80);
//      Serial.print("| motor fast");
//      motor->run(FORWARD);
//    }
//    else if (motorSpeed == "0") {
//      motor->setSpeed(40);
//      Serial.print("| motor slow");
//      motor->run(FORWARD);
//    }
//    else {
//      motor->setSpeed(10);
//      Serial.print("| nothing?");
//      motor->run(FORWARD);
//    }
  }
}
