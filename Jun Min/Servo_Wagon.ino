#include<Arduino.h>
#include<Wire.h>
#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60, MOTOR_DRIVER_BOARD_V5);
Emakefun_Servo *servoLeft = mMotorDriver.getServo(1); //port 1
Emakefun_Servo *servoRight = mMotorDriver.getServo(2); //port 2

const int TrigPin = A2;
const int EchoPin = A3;
float distance;
// starting angle for left and right servo
int langle0 = 70;
int langle1 = 0;
int rangle0 = 60;
int rangle1 = 130; 

void setup() {
  // put your setup code here, to run once:
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
  Serial.print("\n"); // (Till here) to see the distance between wagon's content and ultrasonic sensor
  delay(500);
  servoLeft->writeServo(langle0); // setting the servo original position
  servoRight->writeServo(rangle0);
  delay(500);


  if (distance < 5) 
  {
    int r = 0;
    int i = 200;
    tone(A0, i, 500); // to signify Arduino communicating with ROS
    delay(5000);
    tone(A0, i, 500); // to signify Arduino receiving command from ROS
    delay(5000);
    for (int l = 70; l >= 0; l--) // Lifting the wagon
    { 
      r = 130-l;
      servoLeft->writeServo(l);
      servoRight->writeServo(r);
      delay(30);
    }
    delay(2000);
    for (int l = 0; l <= 70; l++) // Grounding the wagon
    {
      r = 130-l;
      servoLeft->writeServo(l);
      servoRight->writeServo(r);
      delay(50);
    }


  }
}
  
