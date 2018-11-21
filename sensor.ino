  
  
  
/**************************************************** 
 *SENSORE DI DISTANZA
 *la funzione dist() restituisce un valore booleano TRUE 
 *se rileva un ostacolo a distanza maggiore di 30cm  
 ****************************************************/
  
  int dist(){

    int trovato = false;                                                     // imposta la variabile che restituisce a false
  
    digitalWrite (TRIG, HIGH);                                        // attraverso il trigger inizia a emettere onde
    delayMicroseconds(10);                                                   // per dieci secondi
    digitalWrite(TRIG,LOW);                                           // e si ferma

  long duration =pulseIn(ECHO, HIGH);                                  //attraverso la funzione pulseIn acquisiamo il segnale tramite il sensore

  long int distanza = 0.036 * duration /2;                                 //calcoliamo la distanza

  Serial.print(" durata: ");                                               //stampiamo sul monitor seriale la durata del segnale e la distanza ottenuta
  Serial.println(duration);
  Serial.print(" distanza: ");

  if (duration >380000) { 
          Serial.println("fuori portata");                                 //segnaliamo se la distanza è fuori dalla portata dello strumento
  
  }else { 
           Serial.print(distanza); 
           Serial.println ("cm");
           Serial.println (" ");
         }
       
//////evitiamo una divisione per zero, sostituendo lo zero con 1000
 if (duration == 0)
   duration == 1000;
   
   long int rval = microsecondsToCentimeters(duration);                    //calcoliamo la distanza in centimetri
 
 
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
  
