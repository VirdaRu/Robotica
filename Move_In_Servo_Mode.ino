#include <Dynamixel_Serial.h>       // Library needed to control Dynamixal servo

#define SERVO_ID (10u)              // ID of which we will set Dynamixel too
#define SERVO_ID2 (0x2B)
#define SERVO_ControlPin (10u)       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate (1000000)   // Baud rate speed which the Dynamixel will be set too (57600)
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode

int Pos = 0;
int MyPos;

void setup(){
    delay(1000);                                                            // Give time for Dynamixel to start on power-up
    
    Dynamixel.begin(SERVO_SET_Baudrate);                                    // We now need to set Ardiuno to the new Baudrate speed
    Dynamixel.setDirectionPin(SERVO_ControlPin);                            // Optional. Set direction control pin
    Dynamixel.setMode(SERVO_ID, SERVO, CW_LIMIT_ANGLE, CCW_LIMIT_ANGLE);    // set mode to SERVO and set angle limits
    Dynamixel.setMode(SERVO_ID2, SERVO, CW_LIMIT_ANGLE, CCW_LIMIT_ANGLE);
    Serial.begin(1000000);
    //Dynamixel.servo(SERVO_ID, 0,355);
    //Dynamixel.servo(SERVO_ID2, 0, 355);
}


void loop(){
 
  Dynamixel.servo(SERVO_ID, 0x280, 0x75);   // Move servo to angle 1(0.088 degree) at speed 100
  Dynamixel.servo(SERVO_ID2,0x280,0x75);  // Move to Position 896 (Hex = 0x380) NorthEast
  delay(3000);
  Dynamixel.ledState(SERVO_ID, true);
  
  Dynamixel.servo(SERVO_ID2,0x380,0x75);
  Dynamixel.servo(SERVO_ID,0x380,0x75);  //  Move servo to max angle at max speed (1023)
  Dynamixel.ledState(SERVO_ID, false);
  delay(3000);
}

void Move()
{
  Dynamixel.servo(SERVO_ID,100,100);  
  Dynamixel.servo(SERVO_ID2,800,100);
  delay(3000);
  Dynamixel.servo(SERVO_ID2, 100, 100);
  Dynamixel.ledState(SERVO_ID, true);
  Dynamixel.ledState(SERVO_ID2, true); 
}
