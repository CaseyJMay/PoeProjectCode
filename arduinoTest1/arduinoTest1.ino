#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor = AFMS.getMotor(1);

int motorSpeed;

char data;
int analog_val;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  pinMode(LED_BUILTIN, OUTPUT);
            
}

void loop() {
  while (Serial.available() > 0) {
    data = Serial.readString().toInt();
    
    if (data == 1) {
      motorSpeed = 255;
      motor->setSpeed(motorSpeed);
      motor->run(FORWARD);
//      Serial.print("LED On");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
    }
    else if (data == 0) {
      motorSpeed = 0;
      motor->setSpeed(motorSpeed);
      motor->run(FORWARD);
//      Serial.print("LED Off");
      digitalWrite(LED_BUILTIN, LOW);
      delay(10); 
    }
    else {
      motor->setSpeed(100);
      motor->run(FORWARD);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  analog_val = analogRead(A3);
  Serial.println(analog_val); 
  
  delay(100);
}
