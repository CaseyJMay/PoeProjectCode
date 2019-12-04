#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1); // Right Motor
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2); // Left Motor

// initialize variable for determining whether to accept new data or not
boolean newData = false;

// Override var - true when directly setting motor speeds, and not via PID
boolean oride = false;

// Motor Speed | Left sensor threshold | Right sensor threshold | Motor override (stop)
int cvals[4] = {0,900,870,1};

// first motor speed | second motor speed
float ampVals[2] = {100, 50};

// Serial Input Work
const byte numChars = 32;
char caseData = 'p';
char inputData[numChars]; // an array to store the received data


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
}


/*
 * read all the data from serial input until a new line appears
 */
void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\0 ';
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
      
      Serial.println("===InputData===");
      Serial.println(inputData);
      Serial.println("newdata");
      
      newData = true;
    }
//    Serial.println(inputData);
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

      Serial.print("Char Val: ");
      Serial.print(ptr);
      Serial.print("Float Val: ");
      Serial.print(amp);
      Serial.println("");
//      printf("'%s'\n", ptr);
      
      ampVals[ampValNdx] = amp;
      ampValNdx++;
      ptr = strtok(NULL, delim);
      amp = atof(ptr);
    }
    newData = false;
  }
}

void printAmpVals() {
  for (int i = 0; i < 3; i++) {
    Serial.println(ampVals[i]);
  }
}
