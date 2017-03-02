#include "ReadersHandler.h"

ReadersHandler::ReadersHandler(){
  byte _ssPins[] = {SS_1_PIN, SS_2_PIN};
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    _mfrc522[reader].PCD_Init(_ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    _mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

void ReadersHandler::readCards(){
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (_mfrc522[reader].PICC_IsNewCardPresent() && _mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);
      Serial.print(F(": Card UID:"));
      String id = dump_byte_array(_mfrc522[reader].uid.uidByte, _mfrc522[reader].uid.size);
      Serial.println(id);
      delay(10);

      _choice = reader+1;
      _cardUid = id;
    } 
  }
}

boolean ReadersHandler::isCardAvailable(){
  return _choice != 0;
}

int ReadersHandler::getChoice(){
  int choice = _choice;
  _choice = 0;
  return choice;
}

String ReadersHandler::getCardUid(){
  return _cardUid;
}



