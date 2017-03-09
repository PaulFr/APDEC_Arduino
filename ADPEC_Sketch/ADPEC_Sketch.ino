
#include <SPI.h>

#include <SoftwareSerial.h>
#include <Nextion.h>


#include "melody.h"
#include "Survey.h"
#include "Api.h"
#include "utils.h"
#include "ReadersHandler.h"


Survey *survey;
Api *api;
ReadersHandler *readers;

SoftwareSerial nextion(2, 3);// Nextion TX to pin 2 and RX to pin 3 of Arduino

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps


void setup() {

  
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();
  
  readers = new ReadersHandler();
  survey = new Survey();
  api = new Api(survey);

 
  
  pinMode(6, OUTPUT);//buzzer
  myNextion.init();



  api->getCurrentSurveyFromServer();
  changeQuestion();
  
}

void loop() {
  
 
  delay(500);

  readers->readCards();
  if(readers->isCardAvailable()){
    int choix = readers->getChoice();
    String uid = readers->getCardUid();
    answer(uid, choix);
  }
  
}

void answer(String cardUid, int reponse){
 Serial.println("Carte #"+cardUid+" choix "+String(reponse));
 api->contributeToSurvey(reponse, cardUid);
 sonne(reponse);
}

void readNewQuestion(){
  Serial.println("coucou");
}

void changeQuestion(){
  myNextion.setComponentText("t01", survey->getTitle());
  myNextion.setComponentText("t02", survey->getSubtitle());
  myNextion.setComponentText("t1", survey->getFirstChoice());
  myNextion.setComponentText("t2", survey->getSecondChoice());
}

void sonne(int type){
  if(type == 1){
    melody_sing(1);
  }
  else{
    melody_sing(2);
  }
}
 





