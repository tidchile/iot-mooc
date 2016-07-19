

#ifndef Orion_h
#define Orion_h
#include "Arduino.h"

#define 	_RXPIN_ 	2
#define 	_TXPIN_ 	3
#define		BaudRate 	9600

class Orion
{
public:
	Orion();
	void Post(const String &_id, const String &_type, 
		const String &_name1, const String &_name2, 
		const String &_valor1, const String &_valor2);

	void Post(const char *_id, const char *_type, const char *_name1) ;
	void Post(const String &_id, const String &_type, 
		const String &_name1, const String &_valor1);

	void Get(const String &_id, const String &_type);
	void Put(const String &_id, const String &_type, 
		const String &_name1, const String &_name2, 
		const String &_valor1, const String &_valor2);

	void Put(const String &_id, const String &_type, 
		const String &_name1, const String &_valor1);
	
	void Iniciar(String _ssid, String _password);
	void Conectar(String port);
private:
	void AT();
	void Reset();
	void Modo();
	void Mux();
	void Desconectar();
};
#endif