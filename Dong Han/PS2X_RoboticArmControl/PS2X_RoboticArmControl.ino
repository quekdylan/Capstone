#include "FourWheelDrive.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
#include<Arduino.h>
#include<Wire.h>
//#include <ros.h>


ProtocolParser *mProtocol = new ProtocolParser();
FourWheelDrive mARM(mProtocol);

byte UpServo = 90;
byte DownServo = 90;
byte LeftServo = 140;
byte RightServo = 90;

char inByte = 0; //Serial port to receive data
int angle = 0;  //Angle value
String temp = "";//Temporary character variables, or use it for the cache

// Ros Node Handler 
//ros::NodeHandle node_handle;

void setup()
{
  Serial.begin(9600);

  mARM.init(M2, M1, M4, M3);
  mARM.InitServo();
  mARM.InitRgb();
  mARM.SetServoBaseDegree(90);
  mARM.SetServoDegree(1, 40);


  E_CONTOROL_FUNC fun = mProtocol->GetServoDegree();
  
  Serial.println(fun);
  //mARM.SetServoDegree(4, UpServo);
  //mARM.SetServoDegree(2, LeftServo);
  //mARM.SetServoDegree(3, RightServo);
}

void loop()
{
  while (Serial.available() > 0) //Determine whether the serial data
  {
    inByte = Serial.read();//Read data, the serial port can only read 1 character
    temp += inByte;//The characters read into temporary variables inside the cache,
    //Continue to determine the serial port there is no data, know all the data read out
    
  }
  temp.trim(); // Remove whitespace characters
  
  //Determine whether the temporary variable is empty
  if (temp != "") {
    angle = temp.toInt();    //Convert variable string type to integer

    // Check if temp equals home
    if(temp.equals("home")){
      mARM.SetServoDegree(3, 0);
      mARM.SetRgbColor(E_RGB_ALL, RGB_GREEN);
      delay(3000);//Delayed 100 milliseconds
    }

    else if(temp.equals("pickup")){
      mARM.SetServoDegree(3, 170);
      mARM.SetRgbColor(E_RGB_ALL, RGB_BLUE);
      delay(3000);//Delayed 100 milliseconds
    }
    
    else{
      Serial.print("Servo degree: ");
      Serial.println(angle);//Output data to the serial port for observation
      mARM.SetServoDegree(3, angle);
    }
    
    

    mARM.LightOff();
  }
  temp = "";//Please see temporary variables
  delay(100);//Delayed 100 milliseconds
}
