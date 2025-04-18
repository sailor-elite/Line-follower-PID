#include <Arduino.h>
#include "BluetoothSerial.h"
#include<iostream>
#include<string>

BluetoothSerial SerialBT;

String PID_Data;

#define SENSOR_L 34
#define SENSOR_R 35

char buf[30];
char* token;
float P = 0.0, I = 0.0, D = 0.0;




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
pinMode(SENSOR_L, INPUT);

}




void loop() {
  // Reading data from IR Sensors
  int LeftSensor = digitalRead(SENSOR_L);
  //int RightSensor = digitalRead(SENSOR_R);
  //
  //Serial.println("R: "); Serial.println(RightSensor);
  Serial.println("L: "); Serial.println(LeftSensor);
if (SerialBT.available()){

  String data = SerialBT.readStringUntil('\n');
  parsing(data);
  Serial.println("P"); Serial.println(P);
  Serial.println("I"); Serial.println(I);
  Serial.println("D"); Serial.println(D);
}
}






