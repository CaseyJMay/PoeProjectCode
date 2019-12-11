#include "arduinoFFT.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
 
#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 2000 //Hz, must be less than 10000 due to ADC

Adafruit_MotorShield AFMS1 = Adafruit_MotorShield(0x60); 
Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(0x61);
Adafruit_MotorShield AFMS3 = Adafruit_MotorShield(0x62);
Adafruit_MotorShield AFMS4 = Adafruit_MotorShield(0x63); 
Adafruit_MotorShield AFMS5 = Adafruit_MotorShield(0x64); 
Adafruit_DCMotor *motor1 = AFMS1.getMotor(3);
Adafruit_DCMotor *motor2 = AFMS2.getMotor(4);
Adafruit_DCMotor *motor3 = AFMS3.getMotor(4);
Adafruit_DCMotor *motor4 = AFMS4.getMotor(3);
Adafruit_DCMotor *motor5 = AFMS5.getMotor(3);

arduinoFFT FFT = arduinoFFT();

/////////////////////////
#ifndef ARDPRINTF
#define ARDPRINTF
#define ARDBUFFER 16 //Buffer for storing intermediate strings. Performance may vary depending on size.
#include <stdarg.h>
#include <Arduino.h> //To allow function to run from any file in a project

int ardprintf(char *str, ...) //Variadic Function
{
  int i, count=0, j=0, flag=0;
  char temp[ARDBUFFER+1];
  for(i=0; str[i]!='\0';i++)  if(str[i]=='%')  count++; //Evaluate number of arguments required to be printed
  
  va_list argv;
  va_start(argv, count);
  for(i=0,j=0; str[i]!='\0';i++) //Iterate over formatting string
  {
    if(str[i]=='%')
    {
      //Clear buffer
      temp[j] = '\0'; 
      Serial.print(temp);
      j=0;
      temp[0] = '\0';
      
      //Process argument
      switch(str[++i])
      {
        case 'd': Serial.print(va_arg(argv, int));
                  break;
        case 'l': Serial.print(va_arg(argv, long));
                  break;
        case 'f': Serial.print(va_arg(argv, double));
                  break;
        case 'c': Serial.print((char)va_arg(argv, int));
                  break;
        case 's': Serial.print(va_arg(argv, char *));
                  break;
        default:  ;
      };
    }
    else 
    {
      //Add to buffer
      temp[j] = str[i];
      j = (j+1)%ARDBUFFER;
      if(j==0)  //If buffer is full, empty buffer.
      {
        temp[ARDBUFFER] = '\0';
        Serial.print(temp);
        temp[0]='\0';
      }
    }
  };

  Serial.println(); //Print trailing newline
  return count + 1; //Return number of arguments detected
}

#undef ARDBUFFER
#endif
/////////////////////////

// initialize variable for determining whether to accept new data or not
boolean newData = false;
// first motor speed(default speed = 100) | second motor speed(default speed = 50)
float ampVals[5] = {100, 100, 100, 100, 100};
// Serial Input Work
const byte numChars = 32;
char inputData[numChars]; // an array to store the received data

float motor1Speed;
float motor2Speed;
float motor3Speed;
float motor4Speed;
float motor5Speed;

unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];
 
void setup() {
  Serial.begin(115200);
  AFMS1.begin();
  AFMS2.begin();
  AFMS3.begin();
  AFMS4.begin();
  AFMS5.begin();
   
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

  ardprintf("Motor speeds: %f, %f, %f, %f, %f", ampVals[0], ampVals[1], ampVals[2], ampVals[3], ampVals[4]);

  // put your main code here, to run repeatedly:
  motor1Speed = ampVals[0];
  motor2Speed = ampVals[1];
  motor3Speed = ampVals[2];
  motor4Speed = ampVals[3];
  motor5Speed = ampVals[4];
  motor1->setSpeed(motor1Speed);
  motor2->setSpeed(motor2Speed);
  motor3->setSpeed(motor3Speed);
  motor4->setSpeed(motor4Speed);
  motor5->setSpeed(motor5Speed);
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor3->run(FORWARD);
  motor4->run(FORWARD);
  motor5->run(FORWARD);
//  delay(100);

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
      if (ampValNdx == 5) { //changing ampValNdx to three? check if this works
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
