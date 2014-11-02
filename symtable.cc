/* symtable.cc
 * Hash table representing the symbol table.
 * the symbol table.
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#include "symtable.hh"
#include "exception.hh"

Symbol::Symbol(TypenameEntry e, SymbolVariant s) : entry(e), name(e.name) {
	//this->&name = this->entry.name;
	//this->entry = e; /* Should be redundant */
	//this->symb = s;

	std::cout << "Symbol Created:" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Entry: " << this->entry.name << " " << 
			this->entry.category << std::endl;
	std::cout << "Symbol: Something will go here" << std::endl;
}

std::size_t SymbolTable::hash(std::string name) {
	/* 
	 * This code is identical to the Typename Table hash function
	 */
	std::size_t hash = 0;
	const char* s = name.c_str();
	while(*s) {
		hash = hash * 101 + *s++;
	}
	return hash % this->HASHTABLE_SIZE;
}

bool SymbolTable::insert(std::string n, Symbol s) {
	try {
		this->get_symbol(n);
	} catch(ENoSymbolEntry e) {
		/* Symbol wasn't found which is actually what we want. */
		std::size_t h = this->hash(n);
		this->bucket[h].push_back(s);
		return true; /* TODO: Make sure symbol was actually added. */
	}
	/* Symbol already in table -- redeclaration error */
	return false;
}

Symbol SymbolTable::get_symbol(std::string name) {
	std::size_t h = this->hash(name);
	std::deque<Symbol> b = this->bucket[h];
	std::deque<Symbol>::iterator it;
	for(it = b.begin(); it != b.end(); ++it) {
		std::size_t i = it - b.begin();
		if(b[i] == name) {
			return b[i];
		}
	}
	throw ENoSymbolEntry();
}