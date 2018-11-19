#ifndef CBUFFER_H
#define CBUFFER_H

#include <iostream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <cstddef>

/**
@file cbuffer.hpp
@brief Dichiarazione della classe cbuffer
**/

/**
@brief Buffer circolare

Classe templata che rapresenta un buffer circolare, la dimensione è data o 0 di default
**/ 
template <typename T>
class cbuffer{
    public:
        typedef T value_type; ///< Definzione del tipo corrispondente al valore contenuto del cbuffer
        typedef int size_type; ///< Definzione del tipo corrispondente a size, dimensionde del cbuffer
    private:
        size_type _end; ///< Numero di elementi inseriti
        T *_buffer;	///< Puntatore all'array
        size_type _size; ///< Dimensione dell'array
    public:
        /**
		@brief Costruttore di default

		Costruttore di default usato per creare un cbuffer vuoto con size 0
		**/
        cbuffer(): _size(0), _buffer(0), _end(0){
            #ifndef NDEBUG
            std::cout << "cbuffer::cbuffer()" << std::endl;
            #endif
        }

        /**
		@brief Costruttore secondario con size

		Costruttore secondario dove è possibile specificare la size del cbuffer in fase di costruzione
		@param size Dimensione del cbuffer da istanziare 
		**/
        explicit cbuffer(size_type size): _size(0), _buffer(0), _end(0){
            if(size >= 0){
                _buffer = new T[size];
                _size = size;

                #ifndef NDEBUG
                std::cout << "cbuffer::cbuffer(size_type size)" << std::endl;
                #endif
            }
        }

        /**
		@brief Costruttore secondario con size e default value

		Costruttore secondario dove è possibile specificare la size del cbuffer 
		e il valore con cui verrano instanziate tutti i suoi elementi
		@param size Dimensione del cbuffer da instanziare
		@param value Valore usato per instanziare gli elementi del cbuffer
		**/
        cbuffer(size_type size, const T &value): _size(0), _buffer(0), _end(0){
            if(size >= 0){
                _buffer = new T[size];
                _size = size;
                try{
                    for(size_type i = 0; i < size; ++i)
                        _buffer[i] = value;
                    _end = _size;
                }catch(...){
                    clear();
                    throw;
                }
                #ifndef NDEBUG
                std::cout << "cbuffer::cbuffer(size_type size, const T &value)" << std::endl;
                #endif
            }
        }

        /**
		@brief Costruttore secondario con due iteratori

		Costruttore secondario con due iteratori di inizio e fine di una sequenza generica di dati Q e la size,
		la sequenza di dati andrà a riempire con la sequenza di dati il cbuffer instanziato della data dimensione
		@param size Dimensione del cbuffer da instanziare
		@param begin Iteratore che punta al primo elemento della sequenza di dati generici
		@param end Iteratore che punta alla fine della sequenza di dati generici 
		**/
        template <typename iteratorQ>
        cbuffer(size_type size, iteratorQ begin, iteratorQ finish):
            _size(0), _buffer(0), _end(0){
            _buffer = new T[size];
            _size = size;
            try{
                for(; begin != finish; ++begin)
                    insert(*begin);
            }catch(...){
                clear();
                throw;
            }
        }

        /**
		@brief Costruttore per copia

		Costruttore per copia, permette di instanziare un cbuffer con i dati presenti su un altro cbuffer
		passato
		@param other Cbuffer usato per la creazione di quello corrente
		**/
        cbuffer(const cbuffer &other): _size(0), _end(0), _buffer(0){
            _buffer = new T[other._size];
            _size = other._size;
            _end = other._end;

            try {
                if(!empty()){
                    size_type index = 0;//indice in modulo
                    for(size_type i=0; i<_end; ++i){
                        _buffer[i] = other._buffer[i];
                    }
                }
            }
            catch(...) {
                clear();
                throw;
            }

            #ifndef NDEBUG
            std::cout << "cbuffer::cbuffer(const cbuffer&)" << std::endl;
            #endif
        }

        /**
		@brief Operatore assegnamento
		
		Operatore assegnamento, permette la copia di dati di un altro cbuffer tramite swap
 		@param other Cbuffer da cui verrano copia i dati
		@return riferimento a this
		**/
        cbuffer &operator=(const cbuffer &other) {
            if (this != &other) {
                cbuffer tmp(other);
                this->swap(tmp);
            }

            #ifndef NDEBUG
            std::cout << "cbuffer::operator=(const cbuffer&)" << std::endl;
            #endif

            return *this;
	    }

	    /**
		@brief Distruttore

		Distruttore, meotodo fondamentale usato per liberare la memoria allocata dal cbuffer
		**/
	    ~cbuffer(){
	        clear();
	        #ifndef NDEBUG
            std::cout << "~cbuffer()" << std::endl;
            #endif
	    }

		/**
		@brief Swap tra due cbuffer

		Permette lo scambio dei dati tra il cbuffer corrente e quello passato come parametro,
		nello specifico vengono scambiati: size, il puntatore al buffer e il numero di elementi inseriti
		@param other Cbuffer con cui verrano scambiati i dati
		**/		
		void swap(cbuffer &other) {
		    std::swap(other._size, this->_size);
		    std::swap(other._buffer, this->_buffer);
		    std::swap(other._end, this->_end);
	    }

		/**
		@brief Controllo se il cbuffer è vuoto

		Ritorna true se il cbuffer non ha elementi al suo interno, altrimenti ritorna false, 
		@return true se il cbuffer è vuoto altrimenti false 
		**/
        bool empty(){
            return _end == 0;
        }

		/**
		@brief Dimensione del cbuffer

		Ritorna il valore della dimensione del cbuffer
		@return il valore della dimensione del cbuffer
		**/
        size_type size() const {
		    return _size;
	    }
		
		/**
		@brief Inserimento di un elemento in coda al cbuffer

		Permette l'inserimento di un valore in coda al cbuffer, 
		se il cbuffer è pieno il valore inserito andrà a sovrascrivere quello più vecchio già presente del cbuffer,
		se il cbuffer ha dimensione 0 non è possibile inserire il valore 
		**/
	    void insert(const T &value){
			if(_size > 0){
		        if(!full()){
		            _buffer[_end] = value;
		            _end ++;
		        }else{
		            shift_left();
		            _buffer[_end - 1] = value;
		        }
		        //std::cout << "Start:" << _start << std::endl;
		        std::cout << "Added " << value << ", end:" << _end << std::endl;
			}else
				std::cout << "Impossible to add element, the cbuffer size is 0" 
							<< std::endl;
	    }
		
		/**
		@brief Rimozione di un elemento dal cbuffer
		
		Permette la rimozione dell'elemento il testa al cbuffer, cioè quello più vecchio 
		**/
	    void remove(){
			if(!empty()){
	        	shift_left();
	        	_end--;
            	std::cout << "Removed first element, end:" << _end << std::endl;
			}else
				std::cout << "The cbuffer is already empty or the size is 0"
							<< std::endl;
	    }

		/**
		@brief Accesso ai dati in lettura

		Metodo getter per leggere il valore in posizione index-esima del cbuffer, 
		se il valore passato come index è magiore del numero di elementi inseriti nel cbuffer
		genera un eccezione out_of_range che dovrà essere gestita dal chiamante,
		se no restituisce l'elemento in posizione index-esima
		@pre Index deve essere minore del numero di elementi
		@param index Indice della posizione da leggere 
		@return Elemento in posizione index-esima
		**/
	    T &operator[](size_type index) {
	        if(index >= _end)
	            throw std::out_of_range("Index out of range");
	        return _buffer[index];
	    }
			
		/**
		@brief Accesso ai dati in lettura

		Metodo getter per leggere il valore in posizione index-esima del cbuffer, 
		se il valore passato come index è magiore del numero di elementi inseriti nel cbuffer
		genera un eccezione out_of_range che dovrà essere gestita dal chiamante,
		se no restituisce l'elemento in posizione index-esima
		@pre Index deve essere minore del numero di elementi
		@param index Indice della posizione da leggere 
		@return Elemento in posizione index-esima
		**/
        const T &operator[](size_type index) const {
            //index = index % _size;
	        if(index >= _end)
	            throw std::out_of_range("Index out of range");
	        else
	            return _buffer[index];
        }
	
		/**
		@brief Controllo se il cbuffer è pieno

		Restituisce true se il cbuffer è pieno, false altrimenti, 
		è considerato pieno quando il numero di elementi inseriti è uguale alla dimensione dell'array,
		se la dimensione è 0 non viene considerato pieno,
		@return true se è pieno, false se non lo è
		**/
	    bool full(){
	        return _end >= _size && _size > 0;
	    }

	//iteratori ad accesso casuale
    class const_iterator; // forward declaration

	class iterator {
		T *_it;

	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                        value_type;
		typedef ptrdiff_t                difference_type;//
		typedef T*                       pointer;
		typedef T&                       reference;

		iterator(): _it(0){

		}

		iterator(const iterator &other): _it(0) {
			_it = other._it;
		}

		iterator& operator=(const iterator &other) {
			_it = other._it;
		}

		~iterator(){
		    _it = 0;
		}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
            return *_it;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return _it;
		}

		// Operatore di accesso random
		reference operator[](int index) {
            return _it[index];
		}

		// Operatore di iterazione post-incremento
		iterator operator++(int) {
			iterator tmp(*this);
            _it++;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		iterator &operator++() {
			++_it;
			return *this;
		}

		// Operatore di iterazione post-decremento
		iterator operator--(int) {
			iterator tmp(*this);
			_it--;
			return tmp;
		}

		// Operatore di iterazione pre-decremento
		iterator &operator--() {
			--_it;
			return *this;
		}

		// Spostamentio in avanti della posizione
		iterator operator+(int offset) {
			_it += offset;
			return *this;
		}

		// Spostamentio all'indietro della posizione
		iterator operator-(int offset) {
			_it  -= offset;
			return *this;
		}

		// Spostamentio in avanti della posizione
		iterator& operator+=(int offset) {
			_it += offset;
			return *this;
		}

		// Spostamentio all'indietro della posizione
		iterator& operator-=(int offset) {
			_it -= offset;
			return *this;
		}

		// Numero di elementi tra due iteratori
		difference_type operator-(const iterator &other) {
			difference_type diff = _it - other._it;
			if(diff < 0)
			    diff *= -1;
			return diff;
		}

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return _it == other._it;
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return _it != other._it;
		}

		// Confronto
		bool operator>(const iterator &other) const {
			return _it > other._it;
		}


		bool operator>=(const iterator &other) const {
			return _it >= other._it;
		}

		// Confronto
		bool operator<(const iterator &other) const {
			return _it < other._it;
		}


		// Confronto
		bool operator<=(const iterator &other) const {
			return _it <= other._it;
		}


		// Solo se serve anche const_iterator aggiungere le seguenti definizioni

	friend class const_iterator;

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return _it == other._it;
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return _it != other._it;
		}

		// Confronto
		bool operator>(const const_iterator &other) const {
			return _it > other._it;
		}


		bool operator>=(const const_iterator &other) const {
			return _it >= other._it;
		}

		// Confronto
		bool operator<(const const_iterator &other) const {
			return _it < other._it;
		}


		// Confronto
		bool operator<=(const const_iterator &other) const {
			return _it <= other._it;
		}

		// Solo se serve anche const_iterator aggiungere le precedenti definizioni

	private:
		friend class cbuffer;

	    iterator(T* it){
		    _it = it;
		}

	}; // classe iterator

	/**
	@brief Iteratore di inizio della sequenza

	Ritorna l'iteratore all'inizio della sequenza di dati contenuti nel cbuffer
	@return Ritorna l'iteratore all'inizio della sequenza di dati
	**/
	iterator begin() {
		return iterator(_buffer);
	}

	/**
	@brief Iteratore di fine della sequenza

	Ritorna l'iteratore di fine della sequenza di dati contenuti del cbuffer
	@return Ritorna l'iteratore alla fine della sequenza di dati
	**/
	iterator end() {
		return iterator(_buffer + _end);
	}

	class const_iterator {

	    T *_it;

	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                        value_type;
		typedef ptrdiff_t                difference_type;
		typedef const T*                 pointer;
		typedef const T&                 reference;


		const_iterator() {
			_it = 0;
		}

		const_iterator(const const_iterator &other) {
			_it = other._it;
		}

		const_iterator& operator=(const const_iterator &other) {
			_it = other._it;
		}

		~const_iterator() {
			_it = 0;
		}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return *_it;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return _it;
		}

		// Operatore di accesso random
		reference operator[](int index) {
			return _it[index];
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			_it++;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator &operator++() {
			++_it;
			return *this;
		}

		// Operatore di iterazione post-decremento
		const_iterator operator--(int) {
			const_iterator tmp(*this);
			_it--;
			return tmp;
		}

		// Operatore di iterazione pre-decremento
		const_iterator &operator--() {
			--_it;
			return *this;
		}

		// Spostamentio in avanti della posizione
		const_iterator operator+(int offset) {
			_it += offset;
			return *this;
		}

		// Spostamentio all'indietro della posizione
		const_iterator operator-(int offset) {
			_it -= offset;
			return *this;
		}

		// Spostamentio in avanti della posizione
		const_iterator& operator+=(int offset) {
			_it += offset;
			return *this;
		}

		// Spostamentio all'indietro della posizione
		const_iterator& operator-=(int offset) {
			_it -= offset;
			return *this;
		}

		// Numero di elementi tra due iteratori
		difference_type operator-(const const_iterator &other) {
		    difference_type diff = _it - other._it;
			if(diff < 0)
			    diff *= -1;
			return diff;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return _it == other._it;
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return _it != other._it;
		}

		// Confronto
		bool operator>(const const_iterator &other) const {
			return _it > other._it;
		}


		bool operator>=(const const_iterator &other) const {
			return _it >= other._it;
		}

		// Confronto
		bool operator<(const const_iterator &other) const {
			return _it < other._it;
		}


		// Confronto
		bool operator<=(const const_iterator &other) const {
			return _it <= other._it;
		}

		// Solo se serve anche iterator aggiungere le seguenti definizioni

		friend class iterator;

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return _it == other._it;
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return _it != other._it;
		}

		// Confronto
		bool operator>(const iterator &other) const {
			return _it > other._it;
		}


		bool operator>=(const iterator &other) const {
			return _it >= other._it;
		}

		// Confronto
		bool operator<(const iterator &other) const {
			return _it < other._it;
		}


		// Confronto
		bool operator<=(const iterator &other) const {
			return _it <= other._it;
		}

		// Costruttore di conversione iterator -> const_iterator
		const_iterator(const iterator &other) {
			_it = other._it;
		}

		// Assegnamento di un iterator ad un const_iterator
		const_iterator &operator=(const iterator &other) {
			_it = other._it;
		}

		// Solo se serve anche iterator aggiungere le precedenti definizioni

	private:
		friend class cbuffer;

	    const_iterator(T* it){
		    _it = it;
		}

	}; // classe const_iterator

	/**
	@brief Iteratore di inizio della sequenza

	Ritorna l'iteratore all'inizio della sequenza di dati contenuti nel cbuffer
	@return Ritorna l'iteratore all'inizio della sequenza di dati
	**/
	const_iterator begin() const {
		return const_iterator(_buffer);
	}

	/**
	@brief Iteratore di fine della sequenza

	Ritorna l'iteratore alla fine della sequenza di dati contenuti nel cbuffer
	@return Ritorna l'iteratore alla fine della sequenza di dati
	**/
	const_iterator end() const {
		return const_iterator(_buffer + _end);
	}

    private:
		void clear(){
            delete[] _buffer;
	        //_start = -1;
	        _buffer = 0;
	        _size = 0;
	        _end = 0;
        }

        void shift_left(){
            for(size_type i = 1; i < _size; ++i)
                _buffer[i - 1] = _buffer[i];
        }
};

/**
@brief Funzione su predicato unario

La funzione stampa sullo standard input per l'elemento i-esimo del cbuffer true se il predicato con l'elemento i-esimo e vero,
altrimenti false
**/
template<typename P,  typename T>//type of the predicate
void evaluate_if(const cbuffer<T> &cb, P pred){
    typename cbuffer<T>::const_iterator begin = cb.begin();
    typename cbuffer<T>::const_iterator end = cb.end();
    int i;
    for(i = 0; begin != end; ++begin)
        std::cout << "[" << i++ << "]: " << pred(*begin) << std::endl;
}

/**
	@brief Operatore di stream

	Permette di mandare su uno stream di output il contenuto del cbuffer, 
	la funzione manda sullo stream di output i valori contenuti del cbuffer

	@param os stream di output
	@param db cbuffer da utilizzare
	@return Il riferimento allo stream di output
**/

template<typename T>
std::ostream &operator<<(std::ostream &os, const cbuffer<T> &cb){
    typename cbuffer<T>::const_iterator sit, eit;
    sit = cb.begin();
    eit = cb.end();
    if(sit == eit){
        os << "Empty cbuffer";
        return os;
    }
    for(; sit != eit; sit++)
        os << "[" << *sit << "]";
    return os;
}

#endif
