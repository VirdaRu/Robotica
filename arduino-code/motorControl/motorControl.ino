#include "HX711.h"


#define calibration_factor -1098580.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  A2
#define LOADCELL_SCK_PIN  A3


//motor RV/A
const int enRV = 9;
const int inR1 = 8;
const int inR2 = 7;

//motor RA/B
const int enRA = 3;
const int inR3 = 2;
const int inR4 = 4;

//motor LA/C
const int enLA = 11;
const int inL1 = 12;
const int inL2 = 13;

String msg;


HX711 scale;

void setup() {
  Serial.begin(38400);
  //Serial.println("HX711 scale demo");

  //scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.begin(A2, A3);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  pinMode(enRV, OUTPUT);
  pinMode(enRA, OUTPUT);
  pinMode(enLA, OUTPUT);
  pinMode(inR1, OUTPUT);
  pinMode(inR2, OUTPUT);
  pinMode(inR3, OUTPUT);
  pinMode(inR4, OUTPUT); 
  pinMode(inL1, OUTPUT);
  pinMode(inL2, OUTPUT);
}

void loop() {
  readSerialPort();
    
  if(msg=="stop"){
    stopMotors();
    Serial.print("stop");
  }else if(msg=="forward"){
    goForward();
    Serial.print("forward");
  }else if(msg=="reverse"){
    reverse();
    Serial.print("reverse");
  }else if(msg=="right"){
    right();
    Serial.print("right");
  }else if(msg=="left"){
    left();
    Serial.print("left");
  }else if(msg=="weight"){
    Serial.print("Reading: ");
    Serial.print(scale.get_units(), 4); //scale.get_units() returns a float
    Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
  }
  
  delay(2000);
}

void goForward(){
  motorRVfor();
  motorRAfor();
  motorLAfor();
  //turn on motor RV
//  digitalWrite(inR1, LOW);
//  digitalWrite(inR2, HIGH);
//
//  analogWrite(enRV, 200);
//
//  //turn on motor RA
//  digitalWrite(inR3, HIGH);
//  digitalWrite(inR4, LOW);
//
//  analogWrite(enRA, 200);
//
//  //turn on motor LA
//  digitalWrite(inL1, HIGH);
//  digitalWrite(inL2, LOW);
//
//  analogWrite(enLA, 200);
}

void reverse(){
  motorRVrev();
  motorRArev();
  motorLArev();
  //turn on motorA
//  digitalWrite(inR1, HIGH);
//  digitalWrite(inR2, LOW);
//
//  analogWrite(enRV, 200);
//
//  //turn on motorB
//  digitalWrite(inR3, LOW);
//  digitalWrite(inR4, HIGH);
//
//  analogWrite(enRA, 200);
//
//  //motor C
//  digitalWrite(inL1, LOW);
//  digitalWrite(inL2, HIGH);
//
//  analogWrite(enLA, 200);
}

void right(){
  motorRVrev();
  motorRArev();
  motorLAfor();
//  digitalWrite(inR1, HIGH);
//  digitalWrite(inR2, LOW);
//  digitalWrite(inR3, LOW);
//  digitalWrite(inR4, HIGH);
//  digitalWrite(inL1, HIGH);
//  digitalWrite(inL2, LOW);
//
//  analogWrite(enRV, 200);
//  analogWrite(enRA, 200);
//  analogWrite(enLA, 200);
}

void left(){
  motorRVfor();
  motorRAfor();
  motorLArev();
//  digitalWrite(inR1, LOW);
//  digitalWrite(inR2, HIGH);
//  digitalWrite(inR3, HIGH);
//  digitalWrite(inR4, LOW);
//  digitalWrite(inL1, LOW);
//  digitalWrite(inL2, HIGH);
//
//  analogWrite(enRV, 200);
//  analogWrite(enRA, 200);
//  analogWrite(enLA, 200);
}

void stopMotors(){
  digitalWrite(inR1, LOW);
  digitalWrite(inR2, LOW);
  digitalWrite(inR3, LOW);
  digitalWrite(inR4, LOW);
  digitalWrite(inL1, LOW);
  digitalWrite(inL2, LOW);
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
  digitalWrite(inR1, HIGH);
  digitalWrite(inR2, LOW);

  analogWrite(enRV, 200);
}

void motorRVrev(){
  //turn motor RV reverse
  digitalWrite(inR1, LOW);
  digitalWrite(inR2, HIGH);

  analogWrite(enRV, 200);
}

void motorRAfor(){
  //turn motor RA forward
  digitalWrite(inR3, HIGH);
  digitalWrite(inR4, LOW);

  analogWrite(enRA, 200);
}

void motorRArev(){
  //turn motor RA reverse
  digitalWrite(inR3, LOW);
  digitalWrite(inR4, HIGH);

  analogWrite(enRA, 200);
}

void motorLAfor(){
  //turn motor LA forward
  digitalWrite(inL1, HIGH);
  digitalWrite(inL2, LOW);

  analogWrite(enLA, 200);
}

void motorLArev(){
  //turn motor LA reverse
  digitalWrite(inL1, LOW);
  digitalWrite(inL2, HIGH);

  analogWrite(enLA, 200);
}
