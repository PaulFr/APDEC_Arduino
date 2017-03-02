#include "melody.h"
#include "Arduino.h"

int mario_melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0
};
//Mario main them tempo
int mario_tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12
};

//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3
};


void melody_sing(int s) {
  
  if (s == 2) {
    Serial.println(" 'Underworld Theme'");
    playSong(underworld_melody, underworld_tempo, (sizeof(underworld_melody)/sizeof(int)));
  } else {
    Serial.println(" 'Mario Theme'");
    playSong(mario_melody, mario_tempo, (sizeof(mario_melody)/sizeof(int)));
  }

}

void playSong(int melody[], int tempo[], int size){
    Serial.println("taille :");
    Serial.print(sizeof(size));
   for (int thisNote = 0; thisNote < size; thisNote++) {
 
      int noteDuration = 1000 / tempo[thisNote];
 
      buzz(melodyPin, melody[thisNote], noteDuration);
 
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      buzz(melodyPin, 0, noteDuration);
    }
}
 
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; 
  long numCycles = frequency * length / 1000;
  for (long i = 0; i < numCycles; i++) { 
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue); 
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }
  digitalWrite(13, LOW);
}
