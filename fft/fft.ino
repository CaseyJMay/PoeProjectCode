#include "arduinoFFT.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
 
#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 2000 //Hz, must be less than 10000 due to ADC

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);

arduinoFFT FFT = arduinoFFT();

// initialize variable for determining whether to accept new data or not
boolean newData = false;
// first motor speed(default speed = 100) | second motor speed(default speed = 50)
float ampVals[3] = {200, 200, 200};
// Serial Input Work
const byte numChars = 32;
char inputData[numChars]; // an array to store the received data

float motor1Speed;
float motor2Speed;
float motor3Speed;

unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];
 
void setup() {
    Serial.begin(115200);
    AFMS.begin();
 
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}
 
void loop() {
   
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(A3);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    /*PRINT RESULTS*/
//    Serial.println(peak);     //Print out what frequency is the most dominant.
//    Serial.println("---");
    for(int i=0; i<(SAMPLES/2); i++)
    {
        /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
        Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        Serial.print(",");
        Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
    }
 
    delay(1000);  //Repeat the process every second OR:
//    while(1);       //Run code once
    recvWithEndMarker();
    parseNewData();
    
    motor1Speed = ampVals[0];
    motor2Speed = ampVals[1];
    motor3Speed = ampVals[2];
    motor1->setSpeed(motor1Speed);
    motor2->setSpeed(motor2Speed);
    motor3->setSpeed(motor3Speed);
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    motor3->run(FORWARD);
    delay(100);
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
