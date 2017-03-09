#ifndef Api_h
#define Api_h

#include "Arduino.h"
#include "Survey.h"
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>
#include <ArduinoJson.h>

class Api
{
  public:
    Api(Survey* survey);
    void getCurrentSurveyFromServer();
    void contributeToSurvey(int choice, String cardUid);
    JsonObject& readResponse();
    boolean hasStatus();
    String getStatus();
    
  private:
    void _performGet(String url);
    void _performPost(String url, String data);
    void _request();
  
    IPAddress *_ip;
    String _status;
    Survey *_currentSurvey;
    EthernetClient _client;
    char _lastChar;
    boolean _lastState;
    String _response;
    const unsigned long HTTP_TIMEOUT = 10000;  // max respone time from server
    const size_t MAX_CONTENT_SIZE = 512;       // max size of the HTTP response
    byte server[4] = { 192,168,1,2};
    StaticJsonBuffer<150> jsonBuffer;
};

#endif
