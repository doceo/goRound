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

#define TRIG_D A5
#define ECHO_D A4

#define TRIG_A A5
#define ECHO_A A4
 
void setup() {
  // put your setup code here, to run once:
  pinMode (ledPin, OUTPUT);

//sensore distanza
   pinMode(TRIG_D, OUTPUT);
   pinMode(ECHO_D, INPUT);
   pinMode(TRIG_A, OUTPUT);
   pinMode(ECHO_A, INPUT);
  
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
      avantiIndietro(); 
      break;
      
    case 'd':
      avantiIndietro();
      break;

    case 's':
      avantiIndietro();
      break;

    case 'i':
      avantiIndietro();
      break;
    }
  
  }

fermo();
}


/*************************************************************
 * 
 * le seguenti funzioni servono a semplificare la lettura
 * della funzione di loop
 * 
 ************************************************************/

void avantiIndietro(){
  
      inizio = millis();
      avanti();
      
      if (dist()<20){
        
        fermo();
        durata = millis() - inizio;           
      }

 
      inizio = millis();
      indietro();

      delay(durata);

      fermo();

}



/**************************************************************
 * 
 * script modificato a partire da un algoritmo pubblicato 
 * su https://www.lombardoandrea.com/l298n-motore-dc-arduino/
 * 
**************************************************************/


//definizione dei pin
static int In1 = 7; //pin digitale per determinare gli stati logici da inviare al modulo
static int In2 = 3; //pin digitale per determinare gli stati logici da inviare al modulo

static int In3 = 4; //pin digitale per determinare gli stati logici da inviare al modulo
static int In4 = 5; //pin digitale per determinare gli stati logici da inviare al modulo

 
void avviamotore() {
  
  //definisco tipologia pin
  pinMode(In1, OUTPUT); //output perche' definisce lo stato logico del pin IN1 del modulo L298N
  pinMode(In2, OUTPUT); //output perche' definisce lo stato logico del pin IN2 del modulo L298N

  pinMode(In3, OUTPUT); //output perche' definisce lo stato logico del pin IN3 del modulo L298N
  pinMode(In4, OUTPUT); //output perche' definisce lo stato logico del pin IN4 del modulo L298N

 
}
 
 
void avanti() {

  Serial.println();
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  
}


void indietro() {

  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

}


void fermo() {

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void destra(int tempo) {
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  
  delay(tempo);
  fermo();
  
}

void sinistra(int tempo) {
  
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  
  delay(tempo);
  fermo();
  
}

  
  
  
/******************************************************* 
 *SENSORE DI DISTANZA hc-sr04
 *la funzione dist() restituisce un valore booleano TRUE 
 *se rileva un ostacolo a distanza maggiore di 30cm  
 ******************************************************/
  
  int dist(){

    int trovato = false;       
    digitalWrite (TRIG, HIGH);     
    delayMicroseconds(10);   
    digitalWrite(TRIG,LOW);        

  long duration =pulseIn(ECHO, HIGH); 

  long int distanza = 0.036 * duration /2; 

  Serial.print(" durata: ");    
  Serial.println(duration);
  Serial.print(" distanza: ");

  if (duration >380000) { 
          Serial.println("fuori portata");  
  
  }else { 
           Serial.print(distanza); 
           Serial.println ("cm");
           Serial.println (" ");
         }
       
 if (duration == 0)
   duration == 1000;
   
   long int rval = microsecondsToCentimeters(duration);
 
 
 return rval;

}

long microsecondsToCentimeters(long microseconds)
  {
   return microseconds / cmconv;
  } 

  
/**************************************************** 
 *SENSORE DI RUMORE
 *se il microfono percepisce un rumore compie 
 *un giro completo
 ****************************************************/
  
void sentoRumore(){


   rumorValue = analogRead(rumorPin);
   if (rumorValue>100){
      Serial.println (rumorValue, DEC);
      
      int rnd =random (0,100);
      bool giro= rnd % 2;


      if (giro) destra(tempoGiro);
      else sinistra(tempoGiro);

  }
}


/**************************************************** 
 *SENSORE APDS-9960
 *se il sensore percepisce un movimento restituisce in 
 *output la direzione da prendere
 ****************************************************/
  
char direzione(uint8_t gesture){

  char dir;
    if(gesture == APDS9960_UP){
      dir= 'i';
    }
    else if(gesture == APDS9960_LEFT){
      dir= 'd';
    }
    else if(gesture == APDS9960_RIGHT){
      dir= 's';
    }
    else if(gesture == APDS9960_DOWN){
      dir= 'a';
    }

  return dir;
}
