  
  
  
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
      dir= 'a';
    }
    else if(gesture == APDS9960_LEFT){
      dir= 's';
    }
    else if(gesture == APDS9960_RIGHT){
      dir= 'd';
    }
    else if(gesture == APDS9960_DOWN){
      dir= 'i';
    }

  return dir;
}
