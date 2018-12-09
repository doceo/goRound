int tempoGiro = 4000;
int mezzoGiro = 2000;
int giroLato = 1000;

int rumorPin = A0;
int ledPin = 13;
int rumorValue = 0;

int MIN_DIST = 20;
int cmconv = 59; 

int TRIG_D = A2;
int ECHO_D = A3;

int TRIG_A = A0;
int ECHO_A = A1;

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  pinMode (ledPin, OUTPUT);

//sensore distanza
   pinMode(TRIG_D, OUTPUT);
   pinMode(ECHO_D, INPUT);
   pinMode(TRIG_A, OUTPUT);
   pinMode(ECHO_A, INPUT);
    
   Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
Serial.println("sensore avanti");
avantiIndietro("avanti");
delay(4000);

Serial.println();
Serial.println("Senrore indietro");
avantiIndietro("indietro");
delay(5000);



}


void avantiIndietro(String dir){

      int trig;
      int echo;
      unsigned long inizio;
      unsigned long percorso;
      unsigned long ritorno;
      
      if (dir.equals("avanti")){
            trig = TRIG_A;
            echo = ECHO_A;
  
            inizio = millis();
            Serial.print("inizio= ");
            Serial.println(inizio);
            avanti();
        
            if (dist(trig, echo)<20){
          
                fermo();
                percorso = millis() - inizio;
                Serial.print("durata= ");
                Serial.println(percorso);           
                }
   
                inizio = millis();
                indietro();
        
                delay(percorso);
        
                fermo();

      }else if(dir.equals("indietro") ){
            trig = TRIG_D;
            echo = ECHO_D;

           inizio = millis();
            indietro();
        
            if (dist(trig, echo)<20){
          
                fermo();
                percorso = millis() - inizio;           
                }
  
   
                inizio = millis();
                avanti();
        
 //               delay(percorso);
        
                fermo();
        
      }

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

 
  int dist(int TRIG, int ECHO){
    
    Serial.print("trig= ");
    Serial.println(TRIG);
    
    Serial.print("echo= ");
    Serial.println(ECHO);
    
    
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
  
