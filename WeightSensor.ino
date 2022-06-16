#include "HX711.h"

#define calibration_factor 1098580.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  A4
#define LOADCELL_SCK_PIN  A5

HX711 scale;

String msg = "";

void setup() {
  Serial.begin(9600);
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
}

void loop() {
  
  //delay(2000);
  
  readSerialPort();
  
  if(msg.indexOf("weight") != -1){
      getWeight();    
  }
}

void getWeight(){
  Serial.print(scale.get_units(), 4); //scale.get_units() returns a float
  Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
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
