/*
 * Orion
 * Transmisión de datos hacia Fiware mediante ESP8266
 * Por Jonattan Silva
 * Demostración de como conectarse con Fiware mediante
 * un Módulo Serial Wifi ESP8266
 * Crea Instancias, Actualiza el Dato y Obtiene el 
 * dato, mediante peticiones del tipo REST
 * Creado el 10 de Febrero del 2016
 * Este Ejemplo es de Uso Públio.
 */

#include <Orion.h>                                  //Cargar Libería Orion.h
#include <SoftwareSerial.h>                         //Cargar Libería SoftwareSerial
Orion orion;                                        //Crear Objeto
  
#define ssid      "ssid"                            //Nombre de Red Wifi
#define password  "password"                        //Contraseña de Red Wifi
#define port      "port"                            //Puero a conectar

#define id        "_id"                             //Identificador de Instancia
#define type      "_type"                           //Tipo de la Instancia
#define name_1    "_name1"                          //Nombre del Atributo 1
#define name_2    "_name2"                          //Nombre del Atributo 2

void setup() {
  Serial.begin(9600);                               //Iniciar Comunicacion Serial
  orion.Iniciar(ssid, password);                    //Conectar a Red Wifi
  orion.Conectar(port);                             //Conectar a Puerto de Fiware
  orion.Post(id,type,name_1,name_2, "0","false");   //Peticion Post para crear Instancia
}

void loop() {
  orion.Conectar(port);                             //Conectar a Puerto de Fiware
  orion.Get(id,type);                               //Obtener Info de Instancia
  delay(5000);                                      //Delay
}
