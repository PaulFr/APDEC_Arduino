#include "Arduino.h"
#include "Api.h"


Api::Api(Survey *survey)
{

  Serial.println("Classe API");
  _currentSurvey = survey;
  _lastState = false;
 
  _ip = new IPAddress(192,168,1,4);

  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  

  char error = 0;
  error = Ethernet.begin(mac);

  if(error == 0){
    error = Ethernet.begin(mac, _ip);
  }
  /*delay(1000);*/
  Serial.println("connecting...");
  delay(1000);
  Serial.println("connected");

  
}

void Api::getCurrentSurveyFromServer(){
  _performGet("/survey/current.php");
  JsonObject& infos = readResponse();
  delay(200);
  _currentSurvey->setTitle(infos["title"]);

  _currentSurvey->setSubtitle(infos["subtitle"]);
  _currentSurvey->setFirstChoice(infos["choice1"]);
  _currentSurvey->setSecondChoice(infos["choice2"]);
  _currentSurvey->setId(infos["id"]);
  _currentSurvey->setAvailable(true);
}

void Api::contributeToSurvey(int choice, String cardUid){
  _performPost("/survey/"+String(_currentSurvey->getId())+"/contribute", "card="+cardUid+"&choice="+String(choice));
}

JsonObject& Api::readResponse(){
  _lastState = _client.connected();

  while(_lastState && _client.connected()){
    if(_client.available()){
        _lastChar = _client.read();
        _response += _lastChar;

        int contentBodyIndex = _response.lastIndexOf("\r\n\r\n");
        if (contentBodyIndex > 0) {
          _response = "";
        }
    }
    _lastState = _client.connected();
  }

  Serial.println();
  Serial.println("Deconnexion !");

  Serial.println(_response);

  JsonObject& root = jsonBuffer.parseObject(_response);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }else{
    Serial.println("Json Parsed");
  }

  _client.stop();
  return root;
}


void Api::_request(){
   if (_client.connect(server, 80)) {
    Serial.println("connected to server");
  } else {
    Serial.println("connection to server failed");
  }
}

void Api::_performPost(String url, String data)
{
  _request();
  Serial.println("Requete POST : "+url+" : "+data);
  _client.println("POST "+url+" HTTP/1.1");   
  _client.println("Host: 169.254.215.185");
  _client.println("Connection: close");
  _client.println(data);
  _client.println("");
}

void Api::_performGet(String url){
  _request();
  Serial.println("Requete GET : "+url);
  _client.println("GET "+url+" HTTP/1.1");   
  _client.println("Host: 169.254.215.185");
  _client.println("Connection: close");
  _client.println("");
}

