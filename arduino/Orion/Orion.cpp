#include "Arduino.h"
#include "Orion.h"

SoftwareSerial esp8266(_RXPIN_,_TXPIN_);

Orion::Orion(void){}

void Orion::Post(String _id, String _type, String _name1, String _name2, String _valor1, String _valor2){

	  String PostData = "{ \"id\": \"" + _id + "\",\"type\": \"" + _type + "\",\"attributes\" : [{\"name\": \"" + _name1 + "\",\"type\": \"float\",\"value\": \"0\"},{\"name\": \"" + _name2 + "\",\"type\": \"boolean\",\"value\": \"false\"}]}";
   	int size_postdata = PostData.length();
  	//Serial.println(PostData);											//For debug
  	String palabra = _name2;
  	String request = "POST /v1/contextEntities/ HTTP/1.1\r\n";
  	request += "Host: ws-fiware.tidnode.cl:80\r\n";
  	request += "User-Agent: Arduino/1.0\r\n";
  	request += "Accept: application/json\r\n";
  	request += "Content-Type: application/json\r\n";
  	request += "Content-Length: ";
  	request += String(size_postdata) + "\r\n";
  	request += "\r\n";
  	request += PostData;
  	request += "\r\n";
  	//Serial.println(request);
  	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";
  	//send_AT_command2(cipSend); //Cambiar por CipSend();
  	String respuesta = "";
  	esp8266.println(cipSend); // Enviar el caracter leido al esp8266
  	unsigned long time = millis();

  	/*
  	while ( (millis() - time < 5000)){
    	while (esp8266.available())
    	{
      	char c = esp8266.read(); 
      	respuesta += c;
    	}
  	}
  	Serial.print(respuesta); //muestra en monitor serie la respuesta del esp8266
  	*/
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find(">"))
    	{
      		Serial.println(F("Listo Para enviar")); //Cambiar frase
      		break;
    	}
    	else {
    		Serial.println(F("Error: No se puede enviar Peticion"));
    		break;
    	}
  	}

	   /*
  	esp8266.println(request);
  	time = millis();
  	while ( (millis() - time < 5000)){
    	while (esp8266.available())
    	{
      	char c = esp8266.read(); 
      	respuesta += c;
    	}
  	}
  	Serial.println(respuesta); //muestra en monitor serie la respuesta del esp8266
  	*/

  	esp8266.println(request);
  	time = millis();
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("\"OK\""))
    	{
      		Serial.println(F("Peticion POST enviada con exito")); //Cambiar frase
      		break;
    	}
    	else {
    		Serial.println(F("Error: No se puede enviar Peticion"));
    		break;
    	}
  	}
  	/*
  	esp8266.flush();
  	esp8266.println("AT+CIPCLOSE");
  	time = millis();

  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("CLOSED"))
    	{
      		Serial.println(F("Conexion Cerrada")); //Cambiar frase
      		break;
    	}
    	else {
    		Serial.println(F("Error al cerrar la conexion."));
    		break;
    	}
  	}
  	*/
}

void Orion::Get(String _id, String _type){
  	String request = "GET /v1/contextEntities/type/";
  	request +=_type;
  	request +="/id/";
  	request += _id;
  	request += "/";
  	request += " HTTP/1.1\r\n";
  	request += "Host: ws-fiware.tidnode.cl:80\r\n";
  	request += "User-Agent: Arduino/1.0\r\n";
  	request += "Accept: application/json\r\n";
  	request += "Content-Type: application/json\r\n";
  	request += "\r\n";
  	//Serial.println(request);

  	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";

  	String respuesta = "";
  	esp8266.println(cipSend);
  	//delay(500);
  	unsigned long time = millis();

  	/*
  	while ( (millis() - time < 6000)){
    	while (esp8266.available())
    	{
      	char c = esp8266.read(); 
      	respuesta += c;
    	}
  	}
  	Serial.print(respuesta); 

  	*/
  	
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find(">"))
    	{
      		Serial.println(F("Listo Para enviar")); //Cambiar frase
      		break;

    	}
    	else {
    		Serial.println(F("Error: No se puede enviar Peticion GET"));
    		break;
    	}
  	}
  	
  	/*
	
  	esp8266.println(request);
  	time = millis();
  	while ( (millis() - time < 5000)){
    	while (esp8266.available())
    	{
      	char c = esp8266.read(); 
      	respuesta += c;
    	}
  	}
  	Serial.println(respuesta); //muestra en monitor serie la respuesta del esp8266
  	*/
  	
  	/*
  	esp8266.println(request);
  	time = millis();
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("\"OK\""))
    	{
      		Serial.println(F("Peticion GET enviada con exito")); //Cambiar frase
      		break;
    	}
    	else {
    		Serial.println(F("Error: No se puede enviar Peticion"));
    		break;
    	}
  	}
  	*/

    
  	//esp8266.flush();
	   esp8266.println(request); 
  	time = millis();
  	while ( millis() - time < 5000)
  	{
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
    	

  	/*
  	esp8266.println("AT+CIPCLOSE");
  	time = millis();

  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("CLOSED"))
    	{
      		Serial.println(F("Conexion Cerrada")); //Cambiar frase
      		break;
    	}
    	else {
    		Serial.println(F("Error al cerrar la conexion."));
    		break;
    	}
  	}
  	*/

  	 Serial.flush();
}

void Orion::Put(String _id, String _type, String _name1, String _name2, String _valor1, String _valor2){
	 String PostData = "{\"attributes\" : [{\"name\": \"" + _name1 + "\",\"type\": \"float\",\"value\": \"" + _valor1 + "\"},{\"name\": \"" + _name2 + "\",\"type\": \"boolean\",\"value\": \""+ _valor2 + "\"}]}";
   	int size_postdata = PostData.length();
  	//Serial.println(PostData);		
  	String request = "PUT /v1/contextEntities/type/" +_type + "/id/" +_id + "/ HTTP/1.1\r\n";
  	request += "Host: ws-fiware.tidnode.cl:80\r\n";
  	request += "User-Agent: Arduino/1.0\r\n";
  	request += "Accept: application/json\r\n";
  	request += "Content-Type: application/json\r\n";
  	request += "Content-Length: ";
  	request += String(size_postdata) + "\r\n";
  	request += "\r\n";
  	request += PostData;
  	request += "\r\n";
  	//Serial.println(request);
  	String cipSend = "AT+CIPSEND=" + String(request.length()) + "\r\n";
  	String respuesta = "";
  	esp8266.println(cipSend);
  	unsigned long time = millis();

  	/*
  	while ( (millis() - time < 5000)){
    	while (esp8266.available())
    	{
      	char c = esp8266.read(); 
      	respuesta += c;
    	}
  	}
  	Serial.print(respuesta); //muestra en monitor serie la respuesta del esp8266
  	*/
  	

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
    /*
	   esp8266.flush();
  	esp8266.println(request); 
    time = millis();
    while ( millis() - time < 5000)
    {
      while (esp8266.available())
      {
          char c = esp8266.read();
          respuesta += c;
      }
      
    }

    //Serial.println(respuesta);
    if (respuesta.indexOf("\"OK\"")!=-1){
      respuesta +="\r\n";
      Serial.println(F("Peticion PUT enviada con exito"));
    }
    
    */
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
    
  	

  	/*
  	esp8266.flush();
  	esp8266.println("AT+CIPCLOSE");
  	time = millis();

  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("CLOSED"))
    	{
      		Serial.println(F("Conexion Cerrada")); //Cambiar frase
      		break;
    	}
    	else {
    		Serial.println(F("Error al cerrar la conexion."));
    		break;
    	}
  	}
  	*/

}

void Orion::Desconectar(){
	esp8266.println("AT+CWQAP"); // Enviar el caracter leido al esp8266
  	unsigned long time = millis();
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("OK"))
    	{
      		Serial.println(F("Desconectado de todo")); //Cambiar frase
      		break;
    	}
    	else {
    		Serial.println(F("Error: No se puede desconectar"));
    		break;
    	}
  	}
}

void Orion::AT(){
	esp8266.println("AT"); // Enviar el caracter leido al esp8266
  	unsigned long time = millis();
  	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("OK"))
    	{
      		Serial.println(F("OK")); //Cambiar frase
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
    		//respuesta +="\r\n";
    		Serial.println(F("Reset OK"));
    		break;
    	}
    	else {
    		Serial.println(F("Error al resetear"));
    		//Serial.println(respuesta);
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
	AT();
	Desconectar();
	Modo();
	Mux();

	delay(50);
	Serial.println(F("Conectando a red Wifi:"));			//eliminar despues, o comentar
	String respuesta = "";
	esp8266.println("AT+CWJAP=\"" + _ssid + "\",\"" + _password + "\"");
	unsigned long time = millis();
	int auxiliar = 1;
	  if (esp8266.available()>0) {
	    while (auxiliar == 1) {
	      while (esp8266.available()) {
	        char c = esp8266.read();
	        respuesta += c;
	      }
	      if (respuesta.indexOf("OK") != -1) {
	      	Serial.println("Conectado a red: " + _ssid);
	        //Serial.println("\r\n");
	        auxiliar = 0;
	      }
	      if ( millis() - time > 9000){
	      	Serial.println(F("No se pudo conectar, reiniciar"));
          while(1);
	      	//break;
	      }
	      	      
	    }
  	}
    
	//Serial.println(respuesta);				//For debug
}

void Orion::Conectar(String _port){
	/*
	esp8266.println("AT+CIPSTART=\"TCP\",\"ws-fiware.tidnode.cl\"," + _port + "\r\n");
	unsigned long time = millis();
	while ( millis() - time < 5000)
  	{
    	if (esp8266.find("OK") == true){
      		Serial.println(F("Conectado a FIWARE"));
      		break;
    	}
    	else {
    		Serial.println(F("Error: No se puede conectar al servidor"));
    		break;
    	}
  	}
  	*/
  	String respuesta = "";
  	esp8266.println("AT+CIPSTART=\"TCP\",\"ws-fiware.tidnode.cl\"," + _port + "\r\n");
	unsigned long time = millis();
  	while ( millis() - time < 5000)
  	{
    	while (esp8266.available())
    	{
      		char c = esp8266.read();
      		respuesta += c;
    	}
  	}
  
  	//Serial.println(respuesta);
  	if (respuesta.indexOf("OK")!=-1 || respuesta.indexOf("CONNECTED")){
    	respuesta +="\r\n";
    	Serial.println(F("Conectado a FIWARE"));
    }
    else {
    	Serial.println(F("Error: No se puede conectar al servidor"));
    }
    	

}




