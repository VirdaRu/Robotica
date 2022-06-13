#include <Dynamixel_Serial.h>       // Library needed to control Dynamixal servo
#include <AX12A.h>
#include "Arduino.h"

#define SERVO_ControlPin (10u)       
#define SERVO_SET_Baudrate (1000000)

//Front Left Leg
#define SERVO_ID10 (10u)
#define CW_Angle10 507        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define Middle_Angle10 818
#define CCW_Angle10 876      // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode

//Left Rear Leg
#define SERVO_ID1 (1u)
#define CW_Angle1 163
#define Middle_Angle1 200
#define CCW_Angle1 511

//Rear Right Leg
#define SERVO_ID2 (2u)
#define CW_Angle2 509
#define Middle_Angle2 822
#define CCW_Angle2 860

//Front Right Leg
#define SERVO_ID43 (43u)
#define CW_Angle43 150
#define Middle_Angle43 380
#define CCW_Angle43 519

//Bek
#define SERVO_ID3 (3u)
#define CW_Angle3 104
#define Middle_Angle3 204
#define CCW_Angle3 508

//Constants
const int PoleMargin = 50; //50
const int Velocity = 150;
const int DelayVal = 200;
const int Deadzone = 150;
const int LegMoveDelay = 2000;


//motor A/RA (rechts achter)
int enA = 13;
int inR1 = 11;
int inR2 = 10;

//motor B/RV (rechts voor)
int enB = 12;
int inR3 = 9;
int inR4 = 8;

//motor C/LA (links achter) 
int enC = 7;
int inL1 = 5;
int inL2 = 4;

//motor D/LV (links voor)
int enD = 6;
int inL3 = 3;
int inL4 = 2;


void setup(){
    delay(1000);                                                            // Give time for Dynamixel to start on power-up
    
    Dynamixel.begin(SERVO_SET_Baudrate); 
    // We now need to set Ardiuno to the new Baudrate speed
    Dynamixel.setDirectionPin(SERVO_ControlPin);                            // Optional. Set direction control pin
    Dynamixel.setMode(SERVO_ID10, SERVO, CW_Angle10, CCW_Angle10);    // set mode to SERVO and set angle limits
    Dynamixel.setMode(SERVO_ID1, SERVO, CW_Angle1, CCW_Angle1);
    Dynamixel.setMode(SERVO_ID2, SERVO, CW_Angle2, CCW_Angle2);    // set mode to SERVO and set angle limits
    Dynamixel.setMode(SERVO_ID43, SERVO, CW_Angle43, CCW_Angle43);
    Serial.begin(SERVO_SET_Baudrate);

    
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(enC, OUTPUT);
    pinMode(enD, OUTPUT);
    pinMode(inR1, OUTPUT);
    pinMode(inR2, OUTPUT);
    pinMode(inR3, OUTPUT);
    pinMode(inR4, OUTPUT); 
    pinMode(inL1, OUTPUT);
    pinMode(inL2, OUTPUT);
    pinMode(inL3, OUTPUT);
    pinMode(inL4, OUTPUT);
}


void loop(){
  delay(5000);
  PolePosition(); 
  
  //delay(5000);
  //UprightPosition();
  GoForward();
  delay(20000);
}

//Using DC Motors go forward
void GoForward()
{
  digitalWrite(inR1, HIGH);
  digitalWrite(inR2, LOW);
  analogWrite(enA, Velocity);

  digitalWrite(inR3, LOW);
  digitalWrite(inR4, HIGH);
  analogWrite(enB, Velocity);

  digitalWrite(inL1, LOW);
  digitalWrite(inL2, HIGH);
  analogWrite(enC, Velocity);

  digitalWrite(inL3, HIGH);
  digitalWrite(inL4, LOW);
  analogWrite(enD, Velocity);
}

//Legs go backward using its ID
void GoReverse()
{
  digitalWrite(inR1, LOW);
  digitalWrite(inR2, HIGH);
  analogWrite(enA, Velocity);

  digitalWrite(inR3, HIGH);
  digitalWrite(inR4, LOW);
  analogWrite(enB, Velocity);

  digitalWrite(inL1, HIGH);
  digitalWrite(inL2, LOW);
  analogWrite(enC, Velocity);

  digitalWrite(inL3, LOW);
  digitalWrite(inL4, HIGH);
  analogWrite(enD, Velocity);
}

//Robot Returns to its upright position still
void UprightPosition()
{
  //Potential delay removal?
  Dynamixel.servo(SERVO_ID10,818, Velocity);  
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID1, 200, Velocity);
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID2, 822, Velocity);
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID43, 200, Velocity);   
}

//Converts walking/standing robot to a driving one
void PronePosition()
{
  Dynamixel.servo(SERVO_ID10,507, Velocity);  
  
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID1, 511, Velocity);
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID2, 509, Velocity);
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID43, 519, Velocity);    
  
}

//Using the DC Motors Go right by accelerating the rights and reversing the lefts
void Right()
{
  digitalWrite(inR1, LOW);
  digitalWrite(inR2, HIGH); //Only returns LOW atm for some reason
  analogWrite(enA, Velocity);

  digitalWrite(inR3, HIGH);
  digitalWrite(inR4, LOW);
  analogWrite(enB, Velocity);

  digitalWrite(inL1, LOW);
  digitalWrite(inL2, HIGH);
  analogWrite(enC, Velocity);

  digitalWrite(inL3, HIGH);
  digitalWrite(inL4, LOW);
  analogWrite(enD, Velocity);
}

//Using the DC Motors Go left by accelerating the lefts and reversing the rights
void Left()
{
  digitalWrite(inR1, HIGH);
  digitalWrite(inR2, LOW); //
  analogWrite(enA, Velocity);

  digitalWrite(inR3, LOW);
  digitalWrite(inR4, HIGH);
  analogWrite(enB, Velocity);

  digitalWrite(inL1, HIGH);
  digitalWrite(inL2, LOW);
  analogWrite(enC, Velocity);

  digitalWrite(inL3, LOW);
  digitalWrite(inL4, HIGH);
  analogWrite(enD, Velocity);
}

//Facefront
void ShowFace()
{
    Dynamixel.servo(SERVO_ID3,Middle_Angle3, Velocity);
}

//2 Methods for picking up an object using its head
//Head Up to create space, so the robot won't move the object
void HeadUp()
{
    Dynamixel.servo(SERVO_ID3, CCW_Angle3, Velocity);
}
//Head Down to Grab object
void HeadDown()
{
    Dynamixel.servo(SERVO_ID3, CW_Angle3, Velocity);
}

//Head 45 DEGREES to create a more aerodynamic robot and crank the voltage up
void PolePosition()
{
  //50
    Dynamixel.servo(SERVO_ID10,507 + PoleMargin, Velocity);  //+
    delay(DelayVal);
    Dynamixel.servo(SERVO_ID1, 511 - PoleMargin, Velocity); //-
    //Dynamixel.servo(SERVO_ID1, 200, Velocity);
    delay(DelayVal);
    //Dynamixel.servo(SERVO_ID2, 822, Velocity);
    Dynamixel.servo(SERVO_ID2, 509  + PoleMargin, Velocity); // +
    delay(DelayVal);
    Dynamixel.servo(SERVO_ID43, 519 - PoleMargin, Velocity); // -
    Dynamixel.servo(SERVO_ID3, Middle_Angle3 + 50, Velocity); 
}
