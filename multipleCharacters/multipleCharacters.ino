#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

// initialize variable for determining whether to accept new data or not
boolean newData = false;

// first motor speed(default speed=100) | second motor speed(default speed=50)
float ampVals[2] = {150, 150};

// Serial Input Work
const byte numChars = 32;
char inputData[numChars]; // an array to store the received data

int motor1Speed;
int motor2Speed;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}


void loop() {
  // Read Serial input, if any
  recvWithEndMarker();
  parseNewData();
  printAmpVals();

  motor1Speed = ampVals[0]; // 130 is the max for each channel
  motor2Speed = ampVals[1];
  Serial.println(motor1Speed);
  Serial.println(motor2Speed);
  motor1->setSpeed(motor1Speed);
  motor2->setSpeed(motor2Speed);
  motor1->run(FORWARD);
  motor2->run(FORWARD);
}


/*
 * read all the data from serial input until a new line appears
 */
void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\0';
  char rc;
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    if (rc != endMarker) {
      inputData[ndx] = rc;
      ndx++;
      
      if (ndx > numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      inputData[ndx] = '\0'; // terminate the string
      ndx = 0;
      
//      Serial.println("===InputData===");
//      Serial.println(inputData);
//      Serial.println("newdata");
      
      newData = true;
    }
  }
}


/*
 * uses serial connection to change the motor speed and right/left sensor threshold and stop/go
 */
void parseNewData() {
  int ampValNdx = 0;
  char delim[] = ",";
  char *ptr = strtok(inputData, delim);
  float amp = atof(ptr);
  
  if (newData == true) {
    while(ptr != NULL)
    {
      if (ampValNdx == 2) {
        ampValNdx = 0;
      }
      
//      Serial.print("Char Val: ");
//      Serial.print(ptr);
//      Serial.print("Float Val: ");
//      Serial.print(amp);
//      Serial.println("");

      ampVals[ampValNdx] = amp;
      ptr = strtok(NULL, delim);
      amp = atof(ptr);
      ampValNdx++;
    }
    newData = false;
  }
}

void printAmpVals() {
  for (int i = 0; i < 3; i++) {
//    Serial.println(ampVals[i]);
  }
}
