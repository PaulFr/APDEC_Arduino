#ifndef Survey_h
#define Survey_h

#include "Arduino.h"


class Survey
{
  public:
    Survey();
    boolean isAvailable();
    String getTitle();
    String getSubtitle();
    String getFirstChoice();
    String getSecondChoice();
    int getId();

    void setTitle(String title);
    void setFirstChoice(String choice);
    void setSecondChoice(String choice);
    void setSubtitle(String subtitle);
    void setId(int id);
    void setAvailable(boolean isAvailable);
    
  private:
    boolean _available;
    String _title;
    String _subtitle;
    String _firstChoice;
    String _secondChoice;
    int _id;
    
};

#endif
