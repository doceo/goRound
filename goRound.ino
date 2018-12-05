/***********************************************
 * 
 * di seguito sono riportate le connessioni dei 
 * sensori ad arduino
 * 
 * DOPPIO PONTE L298N
 * 
 * MOTOR 1
 * In1  pin 7
 * In2  pin 3
 * 
 * MOTOR 2 
 * In3  pin 4
 * In4  pin 5
 * 
 * SENSORE DI DISTANZA hc-sr04 (dietro)
 * echo   A3
 * trigger A2
 * 
 * SENSORE DI DISTANZA hc-sr04 (avanti)
 * echo   A1
 * trigger A0
 * 
 * SENSORE DI RUMORE
 * DIGITAL pin 10
 * 
 * 
 * APDS-9960 Board  Function
 * IMPORTANT: The APDS-9960 can only accept 3.3V!
 *   
 *  3.3V         VCC              Power
 *  GND          GND              Ground
 *  A4           SDA              I2C Data
 *  A5           SCL              I2C Clock
 *  2            INT              Interrupt
 * 
 * 
 *************************************************/

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
unsigned long inizio;
unsigned long durata;
unsigned long ritorno;

/***************************************************
 * istruzioni legate al sensore di distanza hc-sr04
***************************************************/

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
  
//sentoRumore();

uint8_t gesture = apds.readGesture();

char dir;
if (gesture){
  
  dir = direzione(gesture);
  
  switch (dir) {
    
    case 'a':
      avantiTorna(); 
      break;
      
    case 'd':
      destraTorna();
      break;

    case 's':
      sinistraTorna();
      break;

    case 'i':
      indietroTorna();
      break;
}
  
}

fermo();
}
