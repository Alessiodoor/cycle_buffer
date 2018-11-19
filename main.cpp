#include "cbuffer.hpp"
#include "voce.h"
#include <list>

void test_constructors(){
    cbuffer<int> a(3, 0);
    std::cout << "Print a" << std::endl;
    std::cout << a << std::endl;
    cbuffer<int> c(3);
    std::cout << "Print c" << std::endl;
    std::cout << c << std::endl;
    cbuffer<int> d;
    std::cout << "Print d" << std::endl;
    std::cout << d << std::endl;
    cbuffer<int> b(a);
    std::cout << "Print b" << std::endl;
    std::cout << b << std::endl;
    cbuffer<int> f;
    f = a;
    std::cout << "Print f" << std::endl;
    std::cout << f << std::endl;
    std::list<int> l;
    for (int i=1; i<=5; ++i) l.push_back(i);
    std::list<int>::iterator begin = l.begin();
    std::list<int>::iterator end = l.end();
    cbuffer<int> g(3, begin, end);
    std::cout << "Print g" << std::endl;
    std::cout << g << std::endl;
}

void test_insert(){
    cbuffer<int> cb(3);
    for(int i = 0; i < 3; i++)
        cb.insert(i);
    std::cout << cb << std::endl;
    for(int i = 3; i < 5; i++)
        cb.insert(i);
    std::cout << cb << std::endl;
}

void test_empty(){
	cbuffer<int> cb(3);
	std::cout << "Create cbuffer size 3 with no elements" << std::endl;
	if(cb.empty())
		std::cout << "Empty cbuffer" << std::endl;
	else
		std::cout << "Not empty cbuffer" << std::endl;
	for(int i = 0; i < 3; i++)
        cb.insert(i);
	std::cout << "Insert three elements" << std::endl;
	if(cb.empty())
		std::cout << "Empty cbuffer" << std::endl;
	else
		std::cout << "Not empty cbuffer" << std::endl;
	for(int i = 0; i < 3; i++)
        cb.remove();
	std::cout << "Removed three elements" << std::endl;
	if(cb.empty())
		std::cout << "Empty cbuffer" << std::endl;
	else
		std::cout << "Not empty cbuffer" << std::endl;
}

void test_remove(){
	cbuffer<int> cb(3, 0);
	std::cout << "Create cbuffer size 3 with default elements" << std::endl;
	std::cout << cb << std::endl;
	for(int i = 0; i < 3; i++)
        cb.remove();
	std::cout << cb << std::endl;
	cb.insert(3);
	cb.insert(1);
	std::cout << cb << std::endl;
	cb.remove();
	std::cout << cb << std::endl;
	cb.remove();
	std::cout << cb << std::endl;
}

void test_square_operator(){
	cbuffer<int> cb(3);
	for(int i = 0; i < 3; i++)
        cb.insert(i);
	for(int i = 0; i < 3; i++)
        std::cout << cb[i] << std::endl;
	try{
        std::cout << cb[3] << std::endl;
    }catch(...){
        std::cout << "Out of range on index: 3" << std::endl;
    }
	cb.remove();
	for(int i = 0; i < 3; i++){
        try{
        	std::cout << cb[i] << std::endl;
    	}catch(...){
        	std::cout << "Out of range on index: " << i << std::endl;
    	}
	}
}

void test_full(){
	cbuffer<int> cb(3, 0);
	if(cb.full())
		std::cout << "Full cbuffer"<< std::endl;
	else
		std::cout << "Not full cbuffer"<< std::endl;
	cb.remove();
	if(cb.full())
		std::cout << "Full cbuffer"<< std::endl;
	else
		std::cout << "Not full cbuffer"<< std::endl;
	cb.insert(1);
	if(cb.full())
		std::cout << "Full cbuffer"<< std::endl;
	else
		std::cout << "Not full cbuffer"<< std::endl;
}

/**
@brief Funtore maggiore di 0

Funtore usato per il confronto di un elemento intero, 
restituire true se è maggiore di zero altrimenti false
**/
struct greater_zero {
	bool operator()(int a) const {
		return a > 0;
	}
};

/**
@brief Funtore minore di 0

Funtore usato per il confronto di un elemento intero, 
restituire true se è minore di zero altrimenti false
**/
struct less_zero {
	bool operator()(int a) const {
		return a < 0;
	}
};

void test_evaluate_if(){
	greater_zero gtz;
	less_zero ltz;
	cbuffer<int> cb(3);
	cb.insert(2);
	cb.insert(-2);
	cb.insert(3);
	evaluate_if(cb, gtz);
	evaluate_if(cb, ltz);
}

void test_iterators(){
	cbuffer<int> cb(3);
	for(int i = 0; i < 3; i++)
        cb.insert(i);
	std::cout << cb << std::endl;
    cbuffer<int>::iterator begin = cb.begin();
    cbuffer<int>::iterator end = cb.end();
    std::cout << "Value begin: " << *begin << std::endl;
    std::cout << "Value begin[1] " << begin[1] << std::endl;
    std::cout << "(begin - end): " << (begin - end) << std::endl;
	std::cout << "++begin: " << *(++begin) << std::endl;
	std::cout << "begin++: " << *(begin++) << ", begin:" << *begin << std::endl;
	std::cout << "--begin: " << *(--begin) << std::endl;
	std::cout << "begin--: " << *(begin--) << ", begin:" << *begin << std::endl;
	std::cout << "begin += 2: " << *(begin += 2) << std::endl;
	std::cout << "begin -= 2: " << *(begin -= 2) << std::endl;
	std::cout << "begin = begin + 2: " << *(begin = begin + 2) << std::endl;
	std::cout << "begin = begin - 2: " << *(begin = begin - 2) << std::endl;
	std::cout << "begin == end:" << (begin == end) << std::endl;
	std::cout << "begin != end:" << (begin != end) << std::endl;
	std::cout << "begin > end:" << (begin > end) << std::endl;
	std::cout << "begin < end:" << (begin < end) << std::endl;
	std::cout << "begin >= end:" << (begin >= end) << std::endl;
	std::cout << "begin <= end:" << (begin <= end) << std::endl; 
}

void test_const_iterators(){
	cbuffer<int> cb(3);
	for(int i = 0; i < 3; i++)
        cb.insert(i);
	std::cout << cb << std::endl;
    cbuffer<int>::const_iterator begin = cb.begin();
    cbuffer<int>::const_iterator end = cb.end();
    std::cout << "Value begin: " << *begin << std::endl;
    std::cout << "Value begin[1] " << begin[1] << std::endl;
    std::cout << "(begin - end): " << (begin - end) << std::endl;
	std::cout << "++begin: " << *(++begin) << std::endl;
	std::cout << "begin++: " << *(begin++) << ", begin:" << *begin << std::endl;
	std::cout << "--begin: " << *(--begin) << std::endl;
	std::cout << "begin--: " << *(begin--) << ", begin:" << *begin << std::endl;
	std::cout << "begin += 2: " << *(begin += 2) << std::endl;
	std::cout << "begin -= 2: " << *(begin -= 2) << std::endl;
	std::cout << "begin = begin + 2: " << *(begin = begin + 2) << std::endl;
	std::cout << "begin = begin - 2: " << *(begin = begin - 2) << std::endl;
	std::cout << "begin == end:" << (begin == end) << std::endl;
	std::cout << "begin != end:" << (begin != end) << std::endl;
	std::cout << "begin > end:" << (begin > end) << std::endl;
	std::cout << "begin < end:" << (begin < end) << std::endl;
	std::cout << "begin >= end:" << (begin >= end) << std::endl;
	std::cout << "begin <= end:" << (begin <= end) << std::endl; 
}

void test_voce(){
	cbuffer<voce> cb(2);
	cb.insert(voce("Rossi","Luca", "5558372"));
	cb.insert(voce("Bianchi","Paolo", "5558372"));
	cb.remove();
	cb.insert(voce("Verdi","Giovanni", "5558372"));
	std::cout << cb << std::endl;
}

int main(){
    test_constructors();
    test_insert();
	test_remove();
	test_empty();
	test_square_operator();
	test_full();
	test_evaluate_if();
	test_iterators();
	test_const_iterators();
	test_voce();
    return 0;
}
