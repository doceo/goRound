
//script modificato a partire da un algoritmo pubblicato su https://www.lombardoandrea.com/l298n-motore-dc-arduino/



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
