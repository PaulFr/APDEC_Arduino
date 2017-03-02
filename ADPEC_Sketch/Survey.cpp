#include "Arduino.h"
#include "Survey.h"

    Survey::Survey(){
      _available = false;
    }
    boolean Survey::isAvailable(){
      return _available;
    }
    String Survey::getTitle(){
      return _title;
    }
    String Survey::getSubtitle(){
      return _subtitle;
    }
    String Survey::getFirstChoice(){
      return _firstChoice;
    }
    String Survey::getSecondChoice(){
      return _secondChoice;
    }
    int Survey::getId(){
      return _id;
    }

    void Survey::setTitle(String title){
      _title = title;
    }
    void Survey::setFirstChoice(String choice){
      _firstChoice = choice;
    }
    void Survey::setSecondChoice(String choice){
      _secondChoice = choice;
    }
    void Survey::setSubtitle(String subtitle){
      _subtitle = subtitle;
    }
    void Survey::setId(int id){
      _id = id;
    }

    void Survey::setAvailable(boolean isAvailable){
      _available = isAvailable;
    }

