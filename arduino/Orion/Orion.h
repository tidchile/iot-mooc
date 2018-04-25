

#ifndef Orion_h
#define Orion_h
#include "Arduino.h"

#define 	_RXPIN_ 	2
#define 	_TXPIN_ 	3
#define		BaudRate 	9600
#ifndef 	server
	#define 	server		"ws-fiware.tidnode.cl"
#endif

#ifndef 	port
	#define 	port		"1026"
#endif

class Orion
{
public:
	Orion();
	void Post(const String &_id, const String &_type, 
		const String &_attr1, const String &_attr2, 
		const String &_value1, const String &_value2);

	void Post(const String &_id, const String &_type, const String &_attribute);

	void Post(const String &_id, const String &_type, 
		const String &_attr1, const String &_value1);

	void Get();
	void Get(const String &_id, const String &_type);
	void Get(const String &_id, const String &_type, const String &_attribute);
	
	void Put(const String &_id, const String &_type, 
		const String &_attr1, const String &_attr2, 
		const String &_value1, const String &_value2);

	void Put(const String &_id, const String &_type, 
		const String &_attr1, const String &_value1);
	
	void Iniciar(String _ssid, String _password);
	void Conectar(String _port);
	void Conectar(const char *_server, const char *_port);
	void MostrarIP();
private:
	void AT();
	void Reset();
	void Modo();
	void Mux();
	void Desconectar();
};
#endif