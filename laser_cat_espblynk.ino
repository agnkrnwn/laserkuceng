/***************************************************************************************************************
 *  Laser Pointer Pan/Tilt Control using NodeMCU ESP-12 Develop Kit V1.0 & Blynk
 *  Laser Pointer connected to NodeMCU pin D3
 *  Pan Servo (x) connected to NodeMCU pin D1
 *  Tilt Servo (y) connected to NodeMCU pin D2
 *  Downloads, docs, tutorials: http://www.blynk.cc
 *  Blynk library is licensed under MIT license
 *  Based on the original project posted on: http://www.instructables.com/id/Smartphone-Controlled-Cat-Laser
 *  Developed by MJRovai V.2 03 November 2016 
 ********************************************************************************************************************************/
#define SW_VERSION "LaserCat V.2" 

/* NodeMCU */
#include <ESP8266WiFi.h>
char ssid[] = "izzabags-id";
char pass[] = "passworde123sampe8";

/* Blynk */
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth[] = "Ii1ztB4prfEdMW4wDRLEy2eYjHJJLY8M"; // Laser Cat Project

/* Servos */
#include <Servo.h>
Servo xServo;
Servo yServo;

/* Initial joystick readings set the position to neutral */
int xPotReading = 1023/2;
int yPotReading = 1023/2;

/* Integers used for setting the position of the servos */
int xTemp;
int yTemp;

/* Variables for the buttons */
int randState;
int laserState;

/* Laser Pointer d3 */
#define laserPin 0

/* Reads the joystick or sliders in the blynk app and writes the value to "PotReading" variables */
BLYNK_WRITE(V0) 
{
  Serial.print("move X to ");
  Serial.println(param.asInt());
  xPotReading = param.asInt();
}
BLYNK_WRITE(V1) 
{
  Serial.print("move Y to ");
  Serial.println(param.asInt());
  yPotReading = param.asInt();
}

/* Reads the blynk buttons for the laser and the auto mode */
BLYNK_WRITE(V2) 
{
  Serial.print("BUTTON STATE ");
  Serial.println(param.asInt());
  randState = param.asInt();
}
BLYNK_WRITE(V4) 
{
  Serial.print("LASER STATE ");
  Serial.println(param.asInt());
  laserState = param.asInt();
}

void setup()
{
  Serial.begin(115200);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(laserPin, OUTPUT);
  xServo.attach(2); ///d4
  yServo.attach(12); /// d6
}

void loop()
{
  Blynk.run();
  
  if (randState == 0)  //If the auto button is not pressed:
  {                      
    xTemp = map(xPotReading, 0, 1023, 0, 180); //Map the joystick readings to an angle from 0 to 180 
    yTemp = map(yPotReading,0 ,1023, 0, 180); 
    xServo.write(xTemp);                       //Move the servos to our temporary position
    yServo.write(yTemp);
    delay(10);                                 //Delay to prevent errors
   } else randomMode();                            //randomMode function is caled  
  
  if (laserState == 1) digitalWrite(laserPin, HIGH);  
  else digitalWrite(laserPin, LOW); 
}

/******************************************
 * randomMode function
 ******************************************/
void randomMode() {          
  
  int xrand = random(0, 180); //find a random angle 
  int yrand = random(0, 180);
  xServo.write(xrand);        //write this angle to the servo
  yServo.write(yrand);
  delay(500);                 //pause
}
