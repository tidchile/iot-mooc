#include "Arduino.h"
#include "Orion.h"
#include <SoftwareSerial.h>

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    SoftwareSerial esp8266(_RXPIN_,_TXPIN_);
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    #define esp8266 Serial1
#endif


Orion::Orion(){}

void Orion::Post(const String &_id, const String &_type, 
  const String &_attr1, const String &_attr2, 
  const String &_value1, const String &_value2){

  String postData = "{ \"id\": \"" + _id + "\",\"type\": \"" + _type;
  postData +=       "\",\"attributes\" : [{\"name\": \"" + _attr1 + "\",\"type\": \"float\",\"value\": \"0\"},{\"name\": \"" + _attr2;
  postData +=       "\",\"type\": \"boolean\",\"value\": \"false\"}]}";
 	int size_postData = postData.length();

	String request =   "POST /v1/contextEntities/ HTTP/1.1\r\n";
	request +=         "Host: " + String(server) + ":" + String(port) + "\r\n";
	request +=         "User-Agent: Arduino/1.0\r\n";
	request +=         "Accept: application/json\r\n";
	request +=         "Content-Type: application/json\r\n";
	request +=         "Content-Length: " + String(size_postData) + "\r\n";
	request +=         "\r\n";
	request +=         postData;
	request +=         "\r\n";
	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

	esp8266.println(cipSend);
	
  delay(100);
  unsigned long time = millis();
	while ( millis() - time < 5000){
  	if (esp8266.find(">")){
  		Serial.println(F("Listo Para enviar POST"));
  		break;
  	}
  	else {
  		Serial.println(F("Error: No se puede enviar Peticion POST"));
  		break;
  	}
	}

	esp8266.println(request);
  delay(100);
	if (esp8266.find("\"OK\"")){
    Serial.println(F("Peticion POST enviada con exito"));
	}
	else {
		Serial.println(F("Error: No se puede crear Instancia"));
	}
}

void Orion::Post(const String &_id, const String &_type, const String &_attribute ){
  String postData = "{ \"id\": \"" + _id + "\",";
  postData  +=        "\"type\": \"" + _type + "\",";
  postData  +=        "\"attributes\" : [";
  postData  +=          "{\"name\": \"" + _attribute + "\",";
  postData  +=          "\"type\": \"float\",";
  postData  +=          "\"value\": \"0\"}]}";
                      
  int size_postData = postData.length();
  String request =  "POST /v1/contextEntities/ HTTP/1.1\r\n";
  request +=        "Host: " + String(server) + ":" + String(port) + "\r\n";
  request +=        "User-Agent: Arduino/1.0\r\n";
  request +=        "Accept: application/json\r\n";
  request +=        "Content-Type: application/json\r\n";
  request +=        "Content-Length: " + String(size_postData) + "\r\n";
  request +=        "\r\n";
  request +=        postData;
  request +=        "\r\n";
  String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";
  
  esp8266.println(cipSend);
  unsigned long time = millis();
  while ( millis() - time < 5000){
    if (esp8266.find(">")){
      Serial.println(F("Listo Para enviar POST"));
      break;
    }
    else {
      Serial.println(F("Error: No se puede enviar Peticion POST"));
      break;
    }
  }
  
  String response = "";
  esp8266.println(request);
  time = millis();
  while ( millis() - time < 5000){
    if (esp8266.find("\"OK\"")){
        Serial.println(F("Peticion POST enviada. Creacion de instancia realizada"));
        break;
    }
    else {
      Serial.println(F("Error: No se puede enviar Peticion"));
      break;
    }
  }
}

void Orion::Post(const String &_id, const String &_type,
  const String &_attr, const String &_value){
    
  String postData = "{ \"id\": \"" + _id + "\",";
  postData  +=        "\"type\": \"" + _type + "\",";
  postData  +=        "\"attributes\" : [";
  postData  +=          "{\"name\": \"" + _attr + "\",";
  postData  +=          "\"type\": \"float\",";
  postData  +=          "\"value\": \"" + _value + "\"}]}";
                      
  int size_postData = postData.length();
  String request =  "POST /v1/contextEntities/ HTTP/1.1\r\n";
  request +=        "Host: " + String(server) + ":" + String(port) + "\r\n";
  request +=        "User-Agent: Arduino/1.0\r\n";
  request +=        "Accept: application/json\r\n";
  request +=        "Content-Type: application/json\r\n";
  request +=        "Content-Length: " + String(size_postData) + "\r\n";
  request +=        "\r\n";
  request +=        postData;
  request +=        "\r\n";
  String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";
  
  esp8266.println(cipSend);
  unsigned long time = millis();
  while ( millis() - time < 5000){
    if (esp8266.find(">")){
      Serial.println(F("Listo Para enviar POST"));
      break;
    }
    else {
      Serial.println(F("Error: No se puede enviar Peticion POST"));
      break;
    }
  }
  
  String response = "";
  esp8266.println(request);
  time = millis();
  while ( millis() - time < 5000){
    if (esp8266.find("\"OK\"")){
      Serial.println(F("Peticion POST enviada. Creacion de instancia realizada"));
      break;
    }
    else {
      Serial.println(F("Error: No se puede enviar Peticion"));
      break;
    }
  }
}

void Orion::Get(){
  String request = "GET /v1/contextEntities/ HTTP/1.1\r\n";
  request +=       "Host: " + String(server) + ":" + String(port) + "\r\n";
  request +=       "User-Agent: Arduino/1.0\r\n";
  request +=       "Accept: application/json\r\n";
  request +=       "Content-Type: application/json\r\n";
  request +=       "\r\n";
  String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

  String response = "";
  esp8266.println(cipSend);
  delay(100);
  unsigned long time = millis();
  int _flag = 0;
  
  if (esp8266.find(">")){
      Serial.println(F("Listo Para enviar GET"));
      _flag = 1;
    }
  else {
    Serial.println(F("Error: No se puede enviar Peticion GET")); 
  }
  
  if(_flag == 1){
    esp8266.println(request); 
    time = millis();
    while ( millis() - time < 9000){
      while (esp8266.available() > 0 ){
        char c = esp8266.read();
        Serial.print(c);
      }
    }
    if (response.indexOf("\"OK\"")!=-1){
      response +="\r\n";
      Serial.println(F("Peticion GET enviada con exito"));
    }
  }
  Serial.flush();
}

void Orion::Get(const String &_id, const String &_type){
	String request = "GET /v1/contextEntities/type/" + _type + "/id/" + _id + "/ HTTP/1.1\r\n";
	request +=       "Host: " + String(server) + ":" + String(port) + "\r\n";
	request +=       "User-Agent: Arduino/1.0\r\n";
	request +=       "Accept: application/json\r\n";
	request +=       "Content-Type: application/json\r\n";
	request +=       "\r\n";
	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

	String response = "";
	esp8266.println(cipSend);
  delay(100);
	unsigned long time = millis();
  int _flag = 0;
	
  if (esp8266.find(">")){
    	Serial.println(F("Listo Para enviar GET"));
      _flag = 1;
    }
  else {
    Serial.println(F("Error: No se puede enviar Peticion GET")); 
  }
	
  if(_flag == 1){
	  esp8266.println(request); 
  	time = millis();
  	while ( millis() - time < 5000){
    	while (esp8266.available()){
    		char c = esp8266.read();
    		response += c;
    	}
  	}

  	Serial.println(response);
  	if (response.indexOf("\"OK\"")!=-1){
    	response +="\r\n";
    	Serial.println(F("Peticion GET enviada con exito"));
    }
  }
	Serial.flush();
}

void Orion::Get(const String &_id, const String &_type, const String &_attribute){
  String request = "GET /v1/contextEntities/type/" + _type + "/id/" + _id + "/attributes/" + _attribute + "/ HTTP/1.1\r\n";
  request +=       "Host: " + String(server) + ":" + String(port) + "\r\n";
  request +=       "User-Agent: Arduino/1.0\r\n";
  request +=       "Accept: application/json\r\n";
  request +=       "Content-Type: application/json\r\n";
  request +=       "\r\n";
  String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

  String response = "";
  esp8266.println(cipSend);
  delay(100);
  unsigned long time = millis();
  int _flag = 0;
  
  if (esp8266.find(">")){
      Serial.println(F("Listo Para enviar GET"));
      _flag = 1;
    }
  else {
    Serial.println(F("Error: No se puede enviar Peticion GET")); 
  }
  
  if(_flag == 1){
    esp8266.println(request); 
    time = millis();
    while ( millis() - time < 5000){
      while (esp8266.available()){
        char c = esp8266.read();
        response += c;
      }
    }
  
    Serial.println(response);
    if (response.indexOf("\"OK\"")!=-1){
      response +="\r\n";
      Serial.println(F("Peticion GET enviada con exito"));
    }
  }
  Serial.flush();
}

void Orion::Put(const String &_id, const String &_type, 
  const String &_attr1, const String &_attr2, 
  const String &_value1, const String &_value2){

  String putData = "{\"attributes\" : [{\"name\": \"" + _attr1 + "\",\"type\": \"float\",\"value\": \"" + _value1 + "\"},{\"name\": \"";
  putData +=  _attr2 + "\",\"type\": \"boolean\",\"value\": \""+ _value2 + "\"}]}";
 	int size_putData = putData.length();
	String request = "PUT /v1/contextEntities/type/" +_type + "/id/" +_id + "/ HTTP/1.1\r\n";
	request += "Host: " + String(server) + ":" + String(port) + "\r\n";
	request += "User-Agent: Arduino/1.0\r\n";
	request += "Accept: application/json\r\n";
	request += "Content-Type: application/json\r\n";
	request += "Content-Length: ";
	request += String(size_putData) + "\r\n";
	request += "\r\n";
	request += putData;
	request += "\r\n";
	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

	esp8266.println(cipSend);
  delay(100);
	unsigned long time = millis();
  int _flag = 0;
	while ( millis() - time < 5000){
  	if (esp8266.find(">"))
  	{
    		Serial.println(F("Listo Para enviar")); //Cambiar frase
        _flag = 1;
    		break;
  	}
  	else {
  		Serial.println(F("Error: No se puede enviar Peticion PUT"));
  		break;
  	}
	  }
  if(_flag == 1){
  	esp8266.println(request);
  	time = millis();
  	while ( millis() - time < 5000){
    	if (esp8266.find("\"200\""))
    	{
      		Serial.println(F("Peticion PUT enviada con exito"));
      		break;
    	}
    	else {
    		Serial.println(F("Error: Peticion PUT no enviada"));
    		break;
    	}
  	}
  }
}
void Orion::Put(const String &_id, const String &_type, const String &_attr1, const String &_value1){

  String putData =  "{\"attributes\" : ["
                    "{\"name\": \"" + _attr1 + "\",\"type\": \"float\",\"value\": \"" + _value1 + "\"}]}";

  int size_putData = putData.length();  
  String request =  "PUT /v1/contextEntities/type/" + _type + "/id/" + _id + "/ HTTP/1.1\r\n";
  request +=        "Host: " + String(server) + ":" + String(port) + "\r\n";
  request +=        "User-Agent: Arduino/1.0\r\n";
  request +=        "Accept: application/json\r\n";
  request +=        "Content-Type: application/json\r\n";
  request +=        "Content-Length: " + String(size_putData) + "\r\n";
  request +=        "\r\n";
  request +=        putData;
  request +=        "\r\n";
  String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

  esp8266.println(cipSend);

  unsigned long time = millis();
  int _flag = 0;
  while ( millis() - time < 5000){
    if (esp8266.find(">")){
        Serial.println(F("Listo Para enviar")); 
        _flag = 1;
        break;
    }
    else {
      Serial.println(F("Error: No se puede enviar Peticion PUT"));
      break;
    }
  }
  if(_flag == 1){
    esp8266.println(request);
    time = millis();
    while ( millis() - time < 5000){
      if (esp8266.find("\"200\"")){
          Serial.println(F("Peticion PUT enviada con exito"));
          break;
      }
      else {
        Serial.println(F("Error: Peticion PUT no enviada"));
        break;
      }
    }
  }
}

void Orion::Desconectar(){
	esp8266.println("AT+CWQAP");
  	unsigned long time = millis();
  	while ( millis() - time < 5000){
    	if (esp8266.find("OK")){
    		Serial.println(F("Desconectado de todo"));
    		break;
    	}
    	else {
    		Serial.println(F("Error: No se puede desconectar"));
    		break;
    	}
  	}
}
void Orion::AT(){
	esp8266.println("AT"); 
  	unsigned long time = millis();
  	while ( millis() - time < 5000){
    	if (esp8266.find("OK")){
    		Serial.println(F("OK")); 
    		break;
    	}
    	else {
    		Serial.println(F("Error: No hay comunicacion con el modulo"));
    		break;
    	}

  	}
}
void Orion::Reset(){
	String response = "";
	esp8266.println("AT+RST"); 
	delay(100);
	unsigned long time = millis();
	while ( millis() - time < 5000){
  	while (esp8266.available()>0){
  		char c = esp8266.read();
  		response += c;
  	}
  	delay(1000);
  	if ( (response.indexOf("ready") == true) ){
  		Serial.println(F("Reset OK"));
  		break;
  	}
  	else {
  		Serial.println(F("Error al resetear"));
  		break;
  	}
  	
	}
}
void Orion::Modo(){
	esp8266.println("AT+CWMODE=1");
	unsigned long time = millis();
	while ( millis() - time < 5000){
  	if (esp8266.find("OK") == true){
  		Serial.println(F("Configurado como Nodo"));
  		break;
  	}
  	else {
  		Serial.println(F("Error al configurar modo"));
  		break;
  	}
	}
}
void Orion::Mux(){
	esp8266.println("AT+CIPMUX=0");
	unsigned long time = millis();
	while ( millis() - time < 5000){
  	if (esp8266.find("OK") == true){
  		Serial.println(F("Conexion Punto a Punto"));
  		break;
  	}
  	else {
  		Serial.println(F("Error CIPMUX"));
  		break;
  	}
	}
}
void Orion::Iniciar(String _ssid, String _password){

	esp8266.begin(BaudRate);
  char _ssid_buffer[32];
  _ssid.toCharArray(_ssid_buffer, 32);
  
  esp8266.println("AT+CWJAP?");
  unsigned long time = millis();
  
  if (esp8266.find(_ssid_buffer)){
    Serial.println(F("Ya estas conectado a Red"));
    Serial.println("Conectado a red: " + _ssid);
    delay(1000);
  }
  else {
    Serial.println(F("No Conectado a Red"));
    AT();
    Desconectar();
    Modo();
    Mux();
    Serial.println(F("Conectando a red Wifi:"));
    delay(50);
  
    String response = "";
    esp8266.println("AT+CWJAP=\"" + _ssid + "\",\"" + _password + "\"");
    time = millis();
    int auxiliar = 1;
    if (esp8266.available()>0) {
      while (auxiliar == 1) {
        while (esp8266.available()) {
          char c = esp8266.read();
          response += c;
        }
        if (response.indexOf("OK") != -1) {
          Serial.println("Conectado a red: " + _ssid);
          auxiliar = 0;
          break;
        }
        if ( millis() - time > 9000){
          Serial.println(F("No se pudo conectar, reiniciar"));
          while(1);
        }
      }
    }
  }    
}
void Orion::Conectar(String _port){
  	String response = "";
  	esp8266.println("AT+CIPSTART=\"TCP\",\"" + String(server) + "\"," + _port + "\r\n");
    delay(100);
	  unsigned long time = millis();
  	while ( millis() - time < 1000){
    	while (esp8266.available()){
    		char c = esp8266.read();
    		response += c;
    	}
  	}
    
  	if (response.indexOf("OK")!= -1 || response.indexOf("CONNECTED") != -1 ){
    	response +="\r\n";
    	Serial.println(F("Conectado a FIWARE"));
    }
    if (response.indexOf("DISCONNECT") != -1 ){
        Serial.println(F("Error: No se puede conectar al servidor"));
    } 
}

void Orion::Conectar(const char *_server, const char *_port){
  String response = "";
  esp8266.println("AT+CIPSTART=\"TCP\",\"" + String(_server) + "\"," + String(_port) + "\r\n");
  delay(100);
  unsigned long time = millis();
  while ( millis() - time < 1000){
    while (esp8266.available()){
      char c = esp8266.read();
      response += c;
    }
  }
  
  if (response.indexOf("OK")!= -1 || response.indexOf("CONNECTED") != -1 ){
    response +="\r\n";
    Serial.println(F("Conectado a FIWARE"));
  }
  if (response.indexOf("DISCONNECT") != -1 ){
      Serial.println(F("Error: No se puede conectar al servidor"));
  } 
}

void Orion::MostrarIP(){
  String response = "";
  esp8266.println("AT+CIFSR");
  unsigned long time = millis();
  while ( millis() - time < 3000){
    while (esp8266.available() > 0){
      char c = esp8266.read();
      response += c;
    }
  }
  Serial.println(response);
  Serial.flush();
}



