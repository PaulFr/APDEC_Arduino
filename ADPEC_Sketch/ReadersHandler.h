#ifndef ReadersHandler_h
#define ReadersHandler_h

#include "Arduino.h"
#include "utils.h"
#include <MFRC522.h>
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_1_PIN        7         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
#define SS_2_PIN        8          // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1
#define NR_OF_READERS   2



class ReadersHandler
{
  public:
    ReadersHandler();
    void readCards();
    boolean isCardAvailable();
    int getChoice();
    String getCardUid();
    
    
  private:
    int _choice = 0;
    String _cardUid;
    void _setReadersUp();
    MFRC522 _mfrc522[NR_OF_READERS];

};

#endif
