
 



/*
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */

#include <SPI.h>
#include <MFRC522.h>
//#include <LiquidCrystal.h> 

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_1_PIN        7         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
#define SS_2_PIN        8          // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1


#include <SoftwareSerial.h>
#include <Nextion.h>


#include "melody.h"
#include "Survey.h"
#include "Api.h"




#define NR_OF_READERS   2

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

Survey *survey;
Api *api;
String question;
String subQuestion;
String rep1;
String rep2;
String idQuestion;
SoftwareSerial nextion(2, 3);// Nextion TX to pin 2 and RX to pin 3 of Arduino

Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.


void setup() {

  
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  survey = new Survey();
  api = new Api(*survey);
  
  SPI.begin();        // Init SPI bus
  pinMode(6, OUTPUT);//buzzer
  myNextion.init();

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
  question = "Qui gagnera le match ce soir ?";
  subQuestion = "A vous de choisir";
  rep1 = "France";
  rep2 = "Espagne";
  idQuestion = "0001";

  

  


  
}

void loop() {
  
  
  /*bool first = true; 
  while (client.available()) {
    if(first){
      cara = client.read();
       Serial.print("reçu ");
      first=false;
    }
    
    client.read();
    
  }*/
 
  delay(500);
 /* while (client.available()) {
    cara = client.read();
    Serial.print(cara);
  }*/
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);
      Serial.print(F(": Card UID:"));
      String id = dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.print(id);
      delay(10);
      answer(id, reader+1, idQuestion);
      
      changeQuestion(question, subQuestion, rep1, rep2);
//      Serial.println(cara);
      char retour = 'a';
      sonne(retour);
      
      Serial.println();
    } 
  }
}

void answer(String id, int reponse, String idQuestion){
 
}

void readNewQuestion(){
  Serial.println("coucou");
}

void changeQuestion(String question, String subQuestion, String rep1, String rep2){
  myNextion.setComponentText("t01", question);
  myNextion.setComponentText("t02", subQuestion);
  myNextion.setComponentText("t1", rep1);
  myNextion.setComponentText("t2", rep2);
}

void sonne(int type){
  if(type == 1){
    melody_sing(1);
  }
  else{
    melody_sing(2);
  }
}
 



/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
String dump_byte_array(byte *buffer, byte bufferSize) {

  String id = ""; 
  for (byte i = 0; i < bufferSize; i++) {
    id += String(buffer[i], HEX);
  }
  return id;
}

