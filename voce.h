#ifndef VOCE_H
#define VOCE_H

#include <string>
#include <iostream>

/**
	Struct che rappresenta una voce di una rubrica. Una voce
	e' una terna di valori: <cognome, come, numero_tel>. I valori
	sono di tipo stringa.

	@brief Struct che rappresenta una voce di una rubrica.
*/
struct voce {
	std::string cognome; ///< cognome del contatto
	std::string nome; ///< nome del contatto
	std::string ntel; ///< numero telefonico del contatto
	
	/**
		Costruttore di default. Necessario se vogliamo poter
		costruire una voce senza valori particolari. In particolare
		e' l'unico costruttore per poter usare un array di voci.
	*/
	voce() {}
	
	/**
		Costruttore secondario per avere una voce con dei valori 
		particolari.
		@param c cognome del contatto
		@param n nome del contatto
		@param t numero telefonico del contatto
	*/
	voce(const std::string &c, 
			const std::string &n, 
			const std::string &t) : 
			cognome(c), nome(n), ntel(t){} 

	/* NOTA: gli altri metodi fondamentali (assegnamento, copy constructor e distruttore)
	         in questo caso possono non essere definiti in quanto la struct non contiene 
	         puntatori. L'assegnamento, il copy constructor e il distruttore di default 
	         gestiscono correttamente questi dati. Nulla vieta di definirli esplicitamente.
	*/  
};

/**
	Ridefinizione dell'operatore << per scivere il contenuto della voce su stream
	@param os stream di output su cui mandare la voce
	@param v voce da spedire sullo stream
	@return il riferimento allo stream di output
*/
std::ostream &operator<<(std::ostream &os, const voce &v);


#endif
