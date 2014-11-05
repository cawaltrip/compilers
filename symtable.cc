/* symtable.cc
 * Hash table representing the symbol table.
 * the symbol table.
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */
#include <iostream>
#include <string>

#include "symtable.hh"
#include "exception.hh"

AbstractSymbol::AbstractSymbol(std::string n, TypenameEntry t) 
			: name(n), type(t) {
	//this->&name = this->entry.name;
	//this->entry = e; /* Should be redundant */
	//this->symb = s;

	std::cout << "Symbol Created:" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Entry: " << this->type.name << " " << 
			this->type.category << std::endl;
	std::cout << "Symbol: Something will go here" << std::endl;
}
/* 
 * This hashing method is identical to the Typename Table hash method.
 */
std::size_t SymbolTable::hash(std::string name) {
	std::size_t hash = 0;
	const char* s = name.c_str();
	while(*s) {
		hash = hash * 101 + *s++;
	}
	return hash % this->HASHTABLE_SIZE;
}

bool SymbolTable::insert(std::string n, AbstractSymbol s) {
	if(!this->symbol_exists(n)) {
		std::size_t h = this->hash(n);
		this->bucket[h].push_back(s);
		return true;
	}
	return false;
}

AbstractSymbol SymbolTable::get_symbol(std::string name) {
	std::size_t h = this->hash(name);
	std::deque<AbstractSymbol> b = this->bucket[h];
	std::deque<AbstractSymbol>::iterator it;
	for(it = b.begin(); it != b.end(); ++it) {
		std::size_t i = it - b.begin();
		if(b[i] == name) {
			return b[i];
		}
	}
	throw ENoSymbolEntry();
}

/*
 * Will return true if a symbol is found.  If get_symbol throws
 * an ENoSymbolEntry exception, then the symbol isn't in the symbol
 * table.
 */
bool SymbolTable::symbol_exists(std::string name) {
	try {
		this->get_symbol(name);
	} catch(ENoSymbolEntry e) {
		return false;
	}
	return true;
}