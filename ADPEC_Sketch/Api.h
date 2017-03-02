#ifndef Api_h
#define Api_h

#include "Arduino.h"
#include "Survey.h"
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>

class Api
{
  public:
    Api(Survey survey);
    void getCurrentSurveyFromServer();
    void contributeToSurvey(int choice, String cardUid);
    void readResponse();
    boolean hasStatus();
    String getStatus();
    
  private:
    void _performGet(String url);
    void _performPost(String url, String data);
  
    IPAddress *_ip;
    String _status;
    Survey _currentSurvey;
    EthernetClient _client;
};

#endif
