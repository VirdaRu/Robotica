#include "HX711.h"
#include <Dynamixel_Serial.h>   

#define calibration_factor -1098580.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define SERVO_ControlPin (10u)       
#define Baudrate (57600)

//Front Left Leg
#define SERVO_ID10 (10u)
#define CW_Angle10 507        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_Angle10 876      // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode

//Left Rear Leg
#define SERVO_ID1 (1u)
#define CW_Angle1 163
#define CCW_Angle1 511

//Rear Right Leg
#define SERVO_ID2 (2u)
#define CW_Angle2 509
#define CCW_Angle2 860

//Front Right Leg
#define SERVO_ID43 (43u)
#define CW_Angle43 150
#define CCW_Angle43 519

//Bek
#define SERVO_ID3 (3u)
#define CW_Angle3 120
#define CCW_Angle3 508

#define LOADCELL_DOUT_PIN  A4
#define LOADCELL_SCK_PIN  A5

//motor RA/A
const int enRA = 13;
const int inR1 = 11;
const int inR2 = 10;

//motor RV/B
const int enRV = 12;
const int inR3 = 9;
const int inR4 = 8;

//motor LA/C
const int enLA = 7;
const int inL1 = 5;
const int inL2 = 4;

//motor LV/D
const int enLV = 6;
const int inL3 = 3;
const int inL4 = 2;

String msg = "";
bool openBek = true;

int mSpeed = 150; //motorspeed
const int Velocity = 150; //servo velocity
const int DelayVal = 50;

int posFRLeg = 200;//43
int posBRLeg = 822;//2
int posFLLeg = 818;//10
int posBLLeg = 200;//1

HX711 scale;

void setup() {
  //Serial.begin(38400);
  Serial.begin(56700);
  //Serial.println("HX711 scale demo");
  //scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  //scale.begin(A2, A3);
  //scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  //scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  pinMode(enRV, OUTPUT);
  pinMode(enRA, OUTPUT);
  pinMode(enLA, OUTPUT);
  pinMode(enLV, OUTPUT);
  pinMode(inR1, OUTPUT);
  pinMode(inR2, OUTPUT);
  pinMode(inR3, OUTPUT);
  pinMode(inR4, OUTPUT); 
  pinMode(inL1, OUTPUT);
  pinMode(inL2, OUTPUT);
  pinMode(inL3, OUTPUT);
  pinMode(inL4, OUTPUT);
  Dynamixel.begin(56700); 
  
  Dynamixel.setDirectionPin(SERVO_ControlPin);

  Dynamixel.setMode(SERVO_ID10, SERVO, CW_Angle10, CCW_Angle10);    // set mode to SERVO and set angle limits
  Dynamixel.setMode(SERVO_ID1, SERVO, CW_Angle1, CCW_Angle1);
  Dynamixel.setMode(SERVO_ID2, SERVO, CW_Angle2, CCW_Angle2);    // set mode to SERVO and set angle limits
  Dynamixel.setMode(SERVO_ID43, SERVO, CW_Angle43, CCW_Angle43);
  
  //StandPosition();
  //PolePosition();
  ScoopPosition();
  ServoPosition();
}

void loop() { 
  //readSerialPort();
  ScoopPosition();
  if(msg.indexOf("stop") != -1){
    stopMotors();
    //Serial.print("stop");
  }else if(msg.indexOf("forward") != -1){
    //msg.indexOf("forward") != -1
    //getSpeed(msg);
    goForward();
    //Serial.print("forward");
  }else if(msg.indexOf("reverse") != -1){
    reverse();
    //Serial.print("reverse");
  }else if(msg.indexOf("right") != -1){
    right();
    //Serial.print("right");
  }else if(msg.indexOf("left") != -1){
    left();
    //Serial.print("left");
  }else if(msg.indexOf("weight") != -1){
    //getWeight();
    Serial.print("weight");
  }
//  }else if(msg.indexOf("raiseHand") != -1){
//    raiseHand();
//  }

  if(msg.indexOf("up") != -1){
    StandPosition();
    ServoPosition();
  }else if(msg.indexOf("down") != -1){
    PolePosition();
    ServoPosition();
  }

//  if (msg == "BSW0"){
//    PolePosition();
//    Serial.print("pole");
//  }else if(msg == "BSW1"){
//    StandPosition();
//    Serial.print("stand");
//  }else if(msg == "scoop"){
//    //ScoopPosition();
//    Serial.print("scoop");
//  }

  //ServoPosition();
  

//  if (msg == "pole"){
//    PolePosition();
//    Serial.print("pole");
//  }else if(msg == "stand"){
//    StandPosition();
//    Serial.print("stand");
//  }else if(msg == "scoop"){
//    //ScoopPosition();
//    Serial.print("scoop");
//  }
}

void StandPosition()
{
  posFRLeg = 200;//43
  posBRLeg = 822;//2
  posFLLeg = 818;//10
  posBLLeg = 200;//1   
}

void PolePosition(){
  posFRLeg = 469;//43
  posBRLeg = 559;//2
  posFLLeg = 557;//10
  posBLLeg = 461;//1
}

void raiseHand(){
  Dynamixel.servo(SERVO_ID43, 519, Velocity); 
  delay(4000);
  Dynamixel.servo(SERVO_ID43, 200, Velocity); 
}

void ScoopPosition(){
  //verander zodat hij kan scoopen
  posFRLeg = 519;//43
  posBRLeg = 822;//2
  posFLLeg = 507;//10
  posBLLeg = 200;//1
}


void ServoPosition()
{
  Dynamixel.servo(SERVO_ID10, posFLLeg, Velocity);  
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID1, posBLLeg, Velocity);
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID2, posBRLeg, Velocity);
  delay(DelayVal);
  Dynamixel.servo(SERVO_ID43, posFRLeg, Velocity);
}

void goForward(){
  motorRVfor();
  motorRAfor();
  motorLAfor();
  motorLVfor();
}

void reverse(){
  motorRVrev();
  motorRArev();
  motorLArev();
  motorLVrev();
}

void right(){
  motorRVrev();
  motorRArev();
  motorLAfor();
  motorLVfor();
}

void stepRight(){
  motorRVrev();
  motorRArev();
  motorLAfor();
  motorLVfor();
  delay(300);
  stopMotors();
}

void left(){
  motorRVfor();
  motorRAfor();
  motorLArev();
  motorLVrev();
}

void stepLeft(){
  motorRVfor();
  motorRAfor();
  motorLArev();
  motorLVrev();
  delay(300);
  stopMotors();
}

void openMouth(){
  Dynamixel.servo(SERVO_ID3, CCW_Angle3, 40);
}

void closeMouth(){
  if (openBek){
    Dynamixel.servo(SERVO_ID3, CW_Angle3, 40);
    openBek = false;
  }else{
    Dynamixel.servo(SERVO_ID3, CCW_Angle3, 40);
    openBek = true;
  }
}

void stopMotors(){
  digitalWrite(inR1, LOW);
  digitalWrite(inR2, LOW);
  digitalWrite(inR3, LOW);
  digitalWrite(inR4, LOW);
  digitalWrite(inL1, LOW);
  digitalWrite(inL2, LOW);
  analogWrite(enRV, 0);
  analogWrite(enRA, 0);
  analogWrite(enLA, 0);
  analogWrite(enLV, 0);
}

void readSerialPort() {
  msg = "";
  if (Serial.available()) {
    delay(10);
    while (Serial.available() > 0) {
      msg += (char)Serial.read();
    }
    Serial.flush();
  }
}

void motorRVfor(){
  //turn motor RV forward
  digitalWrite(inR3, HIGH);
  digitalWrite(inR4, LOW);

  analogWrite(enRV, mSpeed);
}

void motorRVrev(){
  //turn motor RV reverse
  digitalWrite(inR3, LOW);
  digitalWrite(inR4, HIGH);

  analogWrite(enRV, 200);
}

void motorRAfor(){
  //turn motor RA forward
  digitalWrite(inR1, HIGH);
  digitalWrite(inR2, LOW);

  analogWrite(enRA, mSpeed);
}

void motorRArev(){
  //turn motor RA reverse
  digitalWrite(inR1, LOW);
  digitalWrite(inR2, HIGH);

  analogWrite(enRA, 200);
}

void motorLAfor(){
  //turn motor LA forward
  digitalWrite(inL1, HIGH);
  digitalWrite(inL2, LOW);

  analogWrite(enLA, mSpeed);
}

void motorLArev(){
  //turn motor LA reverse
  digitalWrite(inL1, LOW);
  digitalWrite(inL2, HIGH);

  analogWrite(enLA, mSpeed);
}

void motorLVfor(){
  //turn motor LV forward
  digitalWrite(inL3, HIGH);
  digitalWrite(inL4, LOW);

  analogWrite(enLV, mSpeed);
}

void motorLVrev(){
  //turn motor LV reverse
  digitalWrite(inL3, LOW);
  digitalWrite(inL4, HIGH);

  analogWrite(enLV, mSpeed);
}

void getSpeed(String msg){
  mSpeed = msg.substring(msg.indexOf(":")+1).toInt();
}

void getWeight(){
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 4); //scale.get_units() returns a float
  Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
}
