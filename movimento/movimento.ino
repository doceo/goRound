int tempoGiro = 4000;
int mezzoGiro = 2000;
int giroLato = 1000;
unsigned long inizio;
unsigned long durata;
unsigned long ritorno;


int rumorPin = A0;
int ledPin = 13;
int rumorValue = 0;

#define MIN_DIST 20
int cmconv = 59; 

#define TRIG A5
#define ECHO A4


void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  pinMode (ledPin, OUTPUT);

//sensore distanza
   pinMode(TRIG, OUTPUT);
   pinMode(ECHO, INPUT);
    
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}


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
  
