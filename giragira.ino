/***********************************************
IMPORTANT: The APDS-9960 can only accept 3.3V!
 
 Arduino Pin  APDS-9960 Board  Function
 
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupt

************************************************/

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

int rumorPin = A0;
int ledPin = 13;
int rumorValue = 0;

/********************************
 * variabili legate al movimento
 * il valore è legato al tempo di 
 * rotazione del robottino
********************************/

int tempoGiro = 4000;
int mezzoGiro = 2000;
int giroLato = 1000;

/*istruzioni legate al sensore di distanza*/

#define MIN_DIST 20
int cmconv = 59; 

#define TRIG A5
#define ECHO A4

 
void setup() {
  // put your setup code here, to run once:
  pinMode (ledPin, OUTPUT);

//sensore distanza
   pinMode(TRIG, OUTPUT);
   pinMode(ECHO, INPUT);

  
  Serial.begin(9600);
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //gesture mode will be entered once proximity mode senses something close
  apds.enableProximity(true);
  apds.enableGesture(true);
}


void loop() {
  
sentoRumore();

/************************************************************
* deve girare a destra o sinistra, andare avanti fino 
* all'ostacolo e poi tornare indietro
************************************************************/


fermo();
}
