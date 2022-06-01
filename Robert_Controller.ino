#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>


/*aansluitingen gaan van links naar rechts met de module naar de gebruiker toe gericht
 * Joystick links is aangesloten op: D2, A0, A1
 * Joystick Rechts is aangesloten op: D3, A2, A3
 * BigSwitch 1,2,3,4 zijn aangesloten op D4, D6, D8, D10
 * LittleSwitch 5,6,7,8 zijn aangesloten op D5, D6, D9, D11
 * Display SH1106 is aangesloten op A4 en A5 en displayknop is aangesloten op D12 en heet DSW1
 */


 //Display code start
#include <SPI.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif   
 //Display code end

 //Variables declaratie
int VRx1 = A0;
int VRy1 = A1;
int SW1 = 2;
int VRx2 = A2;
int VRy2 = A3;
int SW2 = 3;
int BSW1 = 4;
int BSW2 = 6;
int BSW3 = 8;
int BSW4 = 10;
int LSW1 = 5;
int LSW2 = 7;
int LSW3 = 9;
int LSW4 = 11;
int DSW1 = 12;

int xPosition1 = 0;
int yPosition1 = 0;
bool SW_state1 = 0;
int mapX1 = 0;
int mapY1 = 0;
int xPosition2 = 0;
int yPosition2 = 0;
bool SW_state2 = 0;
int mapX2 = 0;
int mapY2 = 0;
int oldmapY1 = 0;
int oldmapX1 = 0;
int oldmapY2 = 0;
int oldmapX2 = 0;
bool BSW_state1 = 0;
bool BSW_state2 = 0;
bool BSW_state3 = 0;
bool BSW_state4 = 0;
bool LSW_state1 = 0;
bool LSW_state2 = 0;
bool LSW_state3 = 0;
bool LSW_state4 = 0;
bool DSW_state1 = 0;
int Error_Code = 0;
bool Errorscreen = 0;
int Error = 404;
const unsigned int MAX_MESSAGE_LENGTH = 4;
void(* resetFunc) (void) = 0;


 //begin van de code
void setup() {
  Serial.begin(38400); 

 //Function declaration
  char Errorcodes(int Error);
  int Buttondisplay(bool BS1, bool BS2, bool BS3, bool BS4, bool LS1, bool LS2, bool LS3, bool LS4);

 // Display initialization
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // Display // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();

  //instellen pullup weerstanden voor inputs
  pinMode(VRx1, INPUT);
  pinMode(VRy1, INPUT);
  pinMode(SW1, INPUT_PULLUP); 
  pinMode(VRx2, INPUT);
  pinMode(VRy2, INPUT);
  pinMode(SW2, INPUT_PULLUP); 
  pinMode(BSW1, INPUT_PULLUP); 
  pinMode(BSW2, INPUT_PULLUP); 
  pinMode(BSW3, INPUT_PULLUP);
  pinMode(BSW4, INPUT_PULLUP);
  pinMode(LSW1, INPUT_PULLUP); 
  pinMode(LSW2, INPUT_PULLUP); 
  pinMode(LSW3, INPUT_PULLUP);
  pinMode(LSW4, INPUT_PULLUP);
  pinMode(DSW1, INPUT_PULLUP);
}


 //loopende code
void loop() {
 //receive communications
 while (Serial.available()>0){
  static char message[MAX_MESSAGE_LENGTH];
  static unsigned int message_pos = 0;
  char inByte = Serial.read();//read next available byte in  serial receive buffer
  if(inByte != '\n' && (message_pos<MAX_MESSAGE_LENGTH)){//message coming in 
   message[message_pos] = inByte;
   message_pos++;
  }
  else{
   message[message_pos] = '\0';  // add null character to string
   if(message[0] == '@'){
    message[0] = '0';
    Error = atoi(message);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,10);
    display.println("Error: ");
    display.print(Error);
   }
  message_pos = 0;
  }
 }

  oldmapY1 = mapY1;
  oldmapX1 = mapX1;
  oldmapY2 = mapY2;
  oldmapX2 = mapX2;
  
 //Start reading in joysticks
  xPosition1 = analogRead(VRx1);
  yPosition1 = analogRead(VRy1);
  SW_state1 = digitalRead(SW1);
  mapY1 = map(xPosition1, 0, 1023, -512, 512);
  mapX1 = -map(yPosition1, 0, 1023, -512, 512);
  xPosition2 = analogRead(VRx2);
  yPosition2 = analogRead(VRy2);
  SW_state2 = digitalRead(SW2);
  mapY2 = map(xPosition2, 0, 1023, -512, 512);
  mapX2 = -map(yPosition2, 0, 1023, -512, 512);
  //Print joysticks via serial
  Serial.print("#JS1:");
  Serial.print(mapX1);
  Serial.print(":");
  Serial.print(mapY1);
  Serial.print(":");
  Serial.println(SW_state1);
  Serial.print("#JS2:");
  Serial.print(mapX2);
  Serial.print(":");
  Serial.print(mapY2);
  Serial.print(":");
  //Display Joysticks
  display.drawLine(16,48,(16+oldmapY1*0.02),(48+oldmapX1*0.02), BLACK);
  display.drawLine(16,48,(16+mapY1*0.02),(48+mapX1*0.02), WHITE); 
  display.drawPixel((16+mapY1*0.023), (48+mapX1*0.023), WHITE);  //Show Joystick 2 on display
  display.drawLine(112,48,(112+oldmapY2*0.02),(48+oldmapX2*0.02), BLACK);
  display.drawLine(112,48,(112+mapY2*0.02),(48+mapX2*0.02), WHITE); 
  display.drawPixel((112+mapY2*0.023), (48+mapX2*0.023), WHITE);  //Show Joystick 2 on display


 //Start reading in buttons
  BSW_state1 = digitalRead(BSW1);
  BSW_state2 = digitalRead(BSW2);
  BSW_state3 = digitalRead(BSW3);
  BSW_state4 = digitalRead(BSW4);
  LSW_state1 = digitalRead(LSW1);
  LSW_state2 = digitalRead(LSW2);
  LSW_state3 = digitalRead(LSW3);
  LSW_state4 = digitalRead(LSW4);
  DSW_state1 = digitalRead(DSW1);
  //Print buttons via serial
  Serial.println(SW_state2);
  Serial.print("#BSW1:");
  Serial.print(BSW_state1);
  Serial.print("#BSW2:");
  Serial.print(BSW_state2);
  Serial.print("#BSW3:");
  Serial.print(BSW_state3);
  Serial.print("#BSW4:");
  Serial.println(BSW_state4);
  Serial.print("#LSW1:");
  Serial.print(LSW_state1);
  Serial.print("#LSW2:");
  Serial.print(LSW_state2);
  Serial.print("#LSW3:");
  Serial.print(LSW_state3);
  Serial.print("#LSW4:");
  Serial.println(LSW_state4);
  //dispay functie buttons
  Buttondisplay(BSW_state1,BSW_state2,BSW_state3,BSW_state4,LSW_state1,LSW_state2,LSW_state3,LSW_state4);


 //Roept de error code aan
  if((DSW_state1 == 0 )&( Errorscreen == 0)){
    Errorscreen = 1;
    delay(250);
    Errorcodes(Error);
    
  }
  if((DSW_state1 == 0 )&( Errorscreen == 1)){
    Errorscreen = 0;
    display.drawTriangle(64, 32-10, 64-10, 32+10, 64+10, 32+10, WHITE);
    display.display();
    delay(1000);
    resetFunc();
  }

  

}


int Buttondisplay(int BS1, int BS2, int BS3, int BS4, int LS1, int LS2, int LS3, int LS4){
if(BS1 == 0){ display.drawRect(111, 34, 3, 3, WHITE);  }
else{         display.drawRect(111, 34, 3, 3, BLACK);  
}
if(BS2 == 0){ display.drawRect(125, 47, 3, 3, WHITE);  }
else{         display.drawRect(125, 47, 3, 3, BLACK);  
}
if(BS3 == 0){ display.drawRect(111, 60, 3, 3, WHITE);  }
else{         display.drawRect(111, 60, 3, 3, BLACK);  
}
if(BS4 == 0){ display.drawRect(98, 47, 3, 3, WHITE);  }
else{         display.drawRect(98, 47, 3, 3, BLACK);  
}
if(LS1 == 0){ display.drawRect(15, 34, 3, 3, WHITE);  }
else{         display.drawRect(15, 34, 3, 3, BLACK);  
}
if(LS2 == 0){ display.drawRect(28, 47, 3, 3, WHITE);  }
else{         display.drawRect(28, 47, 3, 3, BLACK);  
}
if(LS3 == 0){ display.drawRect(15, 60, 3, 3, WHITE);  }
else{         display.drawRect(15, 60, 3, 3, BLACK);  
}
if(LS4 == 0){ display.drawRect(2, 47, 3, 3, WHITE);  }
else{         display.drawRect(2, 47, 3, 3, BLACK);  
}
display.display();
}

int Errorcodes(int Error){  
 DSW_state1 = digitalRead(DSW1);
  if(!(Error == 100)){
    display.clearDisplay();
    delay(500);
    display.setCursor(0,0);
    display.setTextSize(1.5);
    display.setTextColor(BLACK, WHITE); // 'inverted' text
     if(Error == 404){
      display.println("-404- De controller is niet met de robot verbonden");
      }
     if(Error == 401){
      display.println("-401- De bluetooth module herkent de robot maar is niet toegestaan om te verbinden");
      }
     if(Error == 202){
      display.println("-202- De bluetooth controller is verbonden");
      }
    display.display();
    return-1;
  }
  else{
    return 1;
  }
}
