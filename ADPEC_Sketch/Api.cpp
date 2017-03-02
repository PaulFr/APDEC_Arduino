#include "Arduino.h"
#include "Api.h"


Api::Api(Survey survey)
{

  Serial.println("Classe API");
  _currentSurvey = survey;
 
  _ip = new IPAddress(169,254,230,210);

  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  byte server[] = { 169,254,230,221};

  //Ethernet.begin(mac, _ip);
  /*delay(1000);*/
  Serial.println("connecting...");

  if (_client.connect(server, 80)) {
    Serial.println("connected");
  } else {
    Serial.println("connection failed");
  }

  
}

void Api::getCurrentSurveyFromServer(){
  _performGet("/survey/current");
}

void Api::contributeToSurvey(int choice, String cardUid){
  _performPost("/survey/"+String(_currentSurvey.getId())+"/contribute", "card="+cardUid+"&choice="+String(choice));
}

void Api::_performPost(String url, String data)
{
  Serial.println("Requete POST : "+url+" : "+data);
  _client.println("POST "+url+" HTTP/1.1");   
  _client.println("Host: 169.254.215.185");
  _client.println("Connection: close");
  _client.println(data);
  _client.println("");
}

void Api::_performGet(String url){
  Serial.println("Requete GET : "+url);
  _client.println("GET "+url+" HTTP/1.1");   
  _client.println("Host: 169.254.215.185");
  _client.println("Connection: close");
  _client.println("");
}

