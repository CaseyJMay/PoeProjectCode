#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor = AFMS.getMotor(1);
//Adafruit_DCMotor *motor = AFMS.getMotor(2);

int analog_val;
int motorSpeed;
int motorSpeed2;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  motorSpeed = 130; // 130 is the max for each channel
  motor->setSpeed(motorSpeed);
  motor->run(FORWARD);
  
//    if (Serial.available()) {
//      Serial.println(Serial.readString());
//      char c = Serial.read();  //gets one byte from serial buffer
//      if (c == ',') {
//        if (readString.length() >0) {
//          Serial.println(readString);
//        }
//      }
//    }
//  while (Serial.available() > 0) {
//    data = Serial.readString().toInt();
//    
//    if (data == 1) {
//      motorSpeed = 170;
//      motor->setSpeed(motorSpeed);
//      motor->run(FORWARD);
//      delay(5);
//    }
//    else if (data == 0) {
//      motorSpeed = 120;
//      motor->setSpeed(motorSpeed);
//      motor->run(FORWARD);
//      delay(5); 
//    }
//    else {
//      motor->setSpeed(100);
//      motor->run(FORWARD);
//    }
//  }
//  analog_val = analogRead(A3);
//  Serial.println(analog_val); 
  
  delay(5);
}
