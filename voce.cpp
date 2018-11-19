#include "voce.h"

std::ostream &operator<<(std::ostream &os, 
	const voce &v) {
	
	/*
		Scriviamo sullo stream di output le tre stringhe che compongono la voce.
		Di solito non si scive la newline alla fine in quanto, generalmente, 
		la new line viene messa dal chiamante. Si evita di avere due newline una 
		di seguito all'altra.
	*/
	os << v.cognome << " " << v.nome << " " << v.ntel;

	return os;
}

