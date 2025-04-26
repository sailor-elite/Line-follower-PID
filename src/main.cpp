#include <Arduino.h>
#include "BluetoothSerial.h"
#include<iostream>
#include<string>

BluetoothSerial SerialBT;

String PID_Data;


// IR sensor Pins
#define SENSOR_L1 33
#define SENSOR_L2 32
#define SENSOR_L3 35
#define SENSOR_L4 34
#define SENSOR_L5 39

// L298N Pins
#define EN_A 25
#define IN_1 26
#define IN_2 27
#define IN_3 14
#define IN_4 12
#define EN_B 13


char buf[30];
char* token;

// P I D parameters
float P = 1.0, I = 0.2, D = 0.3;




void parsing(String data){
  data.toCharArray(buf, sizeof(buf));
  token = strtok(buf," ");
  while (token != NULL)
  {
    if (token[0] == 'P'){
      sscanf(token+1, "%f", &P);
    }
    else if (token[0] == 'I'){
      sscanf(token+1, "%f", &I);
    }
    else if (token[0] == 'D'){
      sscanf(token+1, "%f", &D);
    }
    token = strtok(NULL, " ");
  }
}

void setup() {
Serial.begin(9600);
SerialBT.begin("ESP32PID");
pinMode(SENSOR_L1, INPUT);
pinMode(SENSOR_L2, INPUT);
pinMode(SENSOR_L3, INPUT);
pinMode(SENSOR_L4, INPUT);
pinMode(SENSOR_L5, INPUT);
}




void loop() {
  // Reading data from IR Sensors
  int L1Sensor = digitalRead(SENSOR_L1);
  int L2Sensor = digitalRead(SENSOR_L2);
  int L3Sensor = digitalRead(SENSOR_L3);
  int L4Sensor = digitalRead(SENSOR_L4);
  int L5Sensor = digitalRead(SENSOR_L5);
  //

if (SerialBT.available()){

  String data = SerialBT.readStringUntil('\n');
  parsing(data);
  Serial.println("P"); Serial.println(P);
  Serial.println("I"); Serial.println(I);
  Serial.println("D"); Serial.println(D);
}
}






