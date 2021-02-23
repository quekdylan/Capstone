#include<Arduino.h>
#include<Wire.h>
#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60, MOTOR_DRIVER_BOARD_V5);
Emakefun_Servo *servoLeft = mMotorDriver.getServo(1); //port 1
Emakefun_Servo *servoRight = mMotorDriver.getServo(2); //port 2

// Servo servoRight;
const int TrigPin = A2;
const int EchoPin = A3;
float distance;
int langle0 = 70;
int langle1 = 0;
int rangle0 = 60;
int rangle1 = 130; 
String per = "";

void setup() {
  // put your setup code here, to run once:
  //servoLeft.attach(1); // pin, min, max
  // servoRight.attach(2);
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(A0, OUTPUT);
  mMotorDriver.begin(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  distance = pulseIn(EchoPin, HIGH) / 58.00;
  Serial.print("distance is :");
  Serial.print(distance);
  Serial.print("cm");
  Serial.print("\n");
  delay(500);
  servoLeft->writeServo(langle0);
  servoRight->writeServo(rangle0);
  delay(500);


  if (distance < 4) 
  {
    int r = 0;
    int i = 200;
    tone(A0, i, 500);
    delay(5000);
    tone(A0, i, 500);
    delay(5000);
    for (int l = 70; l >= 0; l--){
      r = 130-l;
      //r = rangle0;
      servoLeft->writeServo(l);
      servoRight->writeServo(r);
      delay(30);
    }
    delay(2000);
    for (int l = 0; l <= 70; l++)
    {
      r = 130-l;
      //r = rangle1;
      servoLeft->writeServo(l);
      servoRight->writeServo(r);
      delay(50);
    }


  }
}
  
