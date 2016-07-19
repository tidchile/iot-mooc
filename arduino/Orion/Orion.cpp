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
  const String &_name1, const String &_name2, 
  const String &_valor1, const String &_valor2){

	  String PostData = "{ \"id\": \"" + _id + "\",\"type\": \"" + _type + "\",\"attributes\" : [{\"name\": \"" + _name1 + "\",\"type\": \"float\",\"value\": \"0\"},{\"name\": \"" + _name2 + "\",\"type\": \"boolean\",\"value\": \"false\"}]}";
   	int size_postdata = PostData.length();

  	String request =   "POST /v1/contextEntities/ HTTP/1.1\r\n";
  	request +=         "Host: ws-fiware.tidnode.cl:1026\r\n";
  	request +=         "User-Agent: Arduino/1.0\r\n";
  	request +=         "Accept: application/json\r\n";
  	request +=         "Content-Type: application/json\r\n";
  	request +=         "Content-Length: " + String(size_postdata) + "\r\n";
  	request +=         "\r\n";
  	request +=         PostData;
  	request +=         "\r\n";
  	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

  	esp8266.println(cipSend);
  	
    delay(100);
    unsigned long time = millis();
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find(">"))
    	{
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
    	if (esp8266.find("\"OK\""))
    	{
      		Serial.println(F("Peticion POST enviada con exito"));
    	}
    	else {
    		Serial.println(F("Error: No se puede crear Instancia"));
    	}
}

void Orion::Post(const char *_id, const char *_type, const char *_name1 ){
    char PostData[200];
    strcpy(PostData,"{ \"id\": \"");
    strcat(PostData, _id);
    strcat(PostData, "\",");
    strcat(PostData, "\"type\": \"");
    strcat(PostData, _type);
    strcat(PostData, "\",");
    strcat(PostData, "\"attributes\" : [");
    strcat(PostData, "{\"name\": \"");
    strcat(PostData, _name1);
    strcat(PostData, "\",");
    strcat(PostData, "\"type\": \"float\",");
    strcat(PostData, "\"value\": \"0\"}]}");

    int size_postdata = strlen(PostData);
    char size_postdata_char[4];
    itoa(size_postdata, size_postdata_char, 10);

    char request[300];
    strcpy(request, "POST /v1/contextEntities/ HTTP/1.1\r\n");
    strcat(request, "Host: ws-fiware.tidnode.cl:1026\r\n");
    strcat(request, "User-Agent: Arduino/1.0\r\n");
    strcat(request, "Accept: application/json\r\n");
    strcat(request, "Content-Type: application/json\r\n");
    strcat(request, "Content-Length: ");
    strcat(request, size_postdata_char);
    strcat(request, "\r\n");
    strcat(request, "\r\n");
    strcat(request, PostData);
    strcat(request, "\r\n");
  
    int   size_request = sizeof(request);
    char  size_request_char[4];
    itoa(size_request, size_request_char,10);

    String cipSend = "AT+CIPSEND=" + String(strlen(request)) + "\r\n";
    String respuesta = "";
  
    esp8266.println(cipSend);

    unsigned long time = millis();
    while ( millis() - time < 5000)
    {
      if (esp8266.find(">"))
      {
          Serial.println(F("Listo Para enviar POST")); 
          break;
      }
      else {
        Serial.println(F("Error: No se puede enviar Peticion POST"));
        break;
      }
    }

    esp8266.println(request);
    time = millis();
    while ( millis() - time < 5000)
    {
      if (esp8266.find("\"OK\""))
      {
          Serial.println(F("Peticion POST enviada con exito")); 
          break;
      }
      else {
        Serial.println(F("Error: No se puede enviar Peticion"));
        break;
      }
    }
}

void Orion::Post(const String &_id, const String &_type,
  const String &_name1, const String &_valor1){
    
    String PostData = "{ \"id\": \"" + _id + "\",";
    PostData  +=      "\"type\": \"" + _type + "\",";
    PostData  +=      "\"attributes\" : [";
    PostData  +=      "{\"name\": \"" + _name1 + "\",";
    PostData  +=      "\"type\": \"float\",";
    PostData  +=      "\"value\": \"" + _valor1 + "\"}]}";
                        
    int size_postdata = PostData.length();
    String request =  "POST /v1/contextEntities/ HTTP/1.1\r\n";
    request +=        "Host: ws-fiware.tidnode.cl:1026\r\n";
    request +=        "User-Agent: Arduino/1.0\r\n";
    request +=        "Accept: application/json\r\n";
    request +=        "Content-Type: application/json\r\n";
    request +=        "Content-Length: " + String(size_postdata) + "\r\n";
    request +=        "\r\n";
    request +=        PostData;
    request +=        "\r\n";
    String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";
    
    esp8266.println(cipSend);
    
    unsigned long time = millis();

    while ( millis() - time < 5000)
    {
      if (esp8266.find(">"))
      {
          Serial.println(F("Listo Para enviar POST"));
          break;
      }
      else {
        Serial.println(F("Error: No se puede enviar Peticion POST"));
        break;
      }
    }
    
    String respuesta = "";
    
    esp8266.println(request);
    time = millis();
    while ( millis() - time < 5000)
    {
      if (esp8266.find("\"OK\""))
      {
          Serial.println(F("Peticion POST enviada. Creacion de instancia realizada")); //Cambiar frase
          break;
      }
      else {
        Serial.println(F("Error: No se puede enviar Peticion"));
        break;
      }
    }

}
void Orion::Get(const String &_id, const String &_type){
  	String request = "GET /v1/contextEntities/type/" + _type + "/id/" + _id + "/ HTTP/1.1\r\n";
  	request +=       "Host: ws-fiware.tidnode.cl:1026\r\n";
  	request +=       "User-Agent: Arduino/1.0\r\n";
  	request +=       "Accept: application/json\r\n";
  	request +=       "Content-Type: application/json\r\n";
  	request +=       "\r\n";
  	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

  	String respuesta = "";
  	esp8266.println(cipSend);
    delay(100);
  	unsigned long time = millis();
    int flag = 0;
  	
    if (esp8266.find(">")){
      	Serial.println(F("Listo Para enviar GET"));
        flag = 1;
      }
    else {
      Serial.println(F("Error: No se puede enviar Peticion GET")); 
    }
  	
    if(flag == 1){
  	  esp8266.println(request); 
    	time = millis();
    	while ( millis() - time < 5000){
      	while (esp8266.available())
      	{
        		char c = esp8266.read();
        		respuesta += c;
      	}
    	}
    
    	Serial.println(respuesta);
      
    	if (respuesta.indexOf("\"OK\"")!=-1){
      	respuesta +="\r\n";
      	Serial.println(F("Peticion GET enviada con exito"));
      }
    }
  	Serial.flush();

}

void Orion::Put(const String &_id, const String &_type, 
  const String &_name1, const String &_name2, 
  const String &_valor1, const String &_valor2){

	  String PostData = "{\"attributes\" : [{\"name\": \"" + _name1 + "\",\"type\": \"float\",\"value\": \"" + _valor1 + "\"},{\"name\": \"";
    PostData +=  _name2 + "\",\"type\": \"boolean\",\"value\": \""+ _valor2 + "\"}]}";
   	int size_postdata = PostData.length();
  	String request = "PUT /v1/contextEntities/type/" +_type + "/id/" +_id + "/ HTTP/1.1\r\n";
  	request += "Host: ws-fiware.tidnode.cl:1026\r\n";
  	request += "User-Agent: Arduino/1.0\r\n";
  	request += "Accept: application/json\r\n";
  	request += "Content-Type: application/json\r\n";
  	request += "Content-Length: ";
  	request += String(size_postdata) + "\r\n";
  	request += "\r\n";
  	request += PostData;
  	request += "\r\n";
  	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";
  	String respuesta = "";
  	esp8266.println(cipSend);
    delay(100);
  	unsigned long time = millis();

  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find(">"))
    	{
      		Serial.println(F("Listo Para enviar")); //Cambiar frase
      		break;
    	}
    	else {
    		Serial.println(F("Error: No se puede enviar Peticion PUT"));
    		break;
    	}
 	  }

  	esp8266.println(request);
  	time = millis();
  	while ( millis() - time < 3000)
  	{
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
void Orion::Put(const String &_id, const String &_type, 
  const String &_name1, const String &_valor1){

    String PostData =  "{\"attributes\" : ["
                      "{\"name\": \"" + _name1 + "\",\"type\": \"float\",\"value\": \"" + _valor1 + "\"}]}";

    int size_postdata = PostData.length();  
    String request =  "PUT /v1/contextEntities/type/" + _type + "/id/" + _id + "/ HTTP/1.1\r\n";
    request +=        "Host: ws-fiware.tidnode.cl:1026\r\n";
    request +=        "User-Agent: Arduino/1.0\r\n";
    request +=        "Accept: application/json\r\n";
    request +=        "Content-Type: application/json\r\n";
    request +=        "Content-Length: " + String(size_postdata) + "\r\n";
    request +=        "\r\n";
    request +=        PostData;
    request +=        "\r\n";
    String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";
    
    esp8266.println(cipSend);
    String respuesta = "";
    unsigned long time = millis();

    while ( millis() - time < 5000)
    {
      if (esp8266.find(">"))
      {
          Serial.println(F("Listo Para enviar")); 
          break;
      }
      else {
        Serial.println(F("Error: No se puede enviar Peticion PUT"));
        break;
      }
    }
  
    esp8266.println(request);
    time = millis();
    while ( millis() - time < 3000)
    {
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

void Orion::Desconectar(){
	esp8266.println("AT+CWQAP");
  	unsigned long time = millis();
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("OK"))
    	{
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
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("OK"))
    	{
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
	String respuesta = "";
  	esp8266.println("AT+RST"); 
  	delay(100);
  	unsigned long time = millis();
  	while ( millis() - time < 5000){
    	while (esp8266.available()>0)
    	{
      		char c = esp8266.read();
      		respuesta += c;
    	}
    	delay(1000);
    	if ( (respuesta.indexOf("ready") == true) ){
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
	while ( millis() - time < 5000)
  	{
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
	while ( millis() - time < 5000)
  	{
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
  
    String respuesta = "";
    esp8266.println("AT+CWJAP=\"" + _ssid + "\",\"" + _password + "\"");
    time = millis();
    int auxiliar = 1;
      if (esp8266.available()>0) {
        while (auxiliar == 1) {
          while (esp8266.available()) {
            char c = esp8266.read();
            respuesta += c;
          }
          if (respuesta.indexOf("OK") != -1) {
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
  	String respuesta = "";


  	esp8266.println("AT+CIPSTART=\"TCP\",\"ws-fiware.tidnode.cl\"," + _port + "\r\n");
    delay(100);
	  unsigned long time = millis();
  	while ( millis() - time < 1000){
    	while (esp8266.available())
    	{
      		char c = esp8266.read();
      		respuesta += c;
    	}
  	}
    
  	if (respuesta.indexOf("OK")!= -1 || respuesta.indexOf("CONNECTED") != -1 ){
    	respuesta +="\r\n";
    	Serial.println(F("Conectado a FIWARE"));
    }
    if (respuesta.indexOf("DISCONNECT") != -1 ){
        Serial.println(F("Error: No se puede conectar al servidor"));
    } 
}



