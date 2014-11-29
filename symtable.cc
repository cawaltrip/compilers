/* symtable.cc
 * Hash table representing the symbol table.
 * the symbol table.
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */
#include <iostream>
#include <sstream>
#include <string>

#include "symtable.hh"
#include "exception.hh"

/*
AbstractSymbol::AbstractSymbol(std::string n, TypenameEntry t) 
			: name(n), type(t) { }
*/
AbstractSymbol::AbstractSymbol(std::string n, std::string t)
			: name(n), type(t) { }
std::string AbstractSymbol::to_string(std::size_t depth) {
	std::string spaces = std::string(depth, '>');
	return(spaces + this->type + " " + this->name);
}

/* 
 * The only time that SymbolTable's parent will be NULL is the Global Symbol
 * Table.  Given this and the n-ary tree (represented using std::deque),
 * resolving scope should be relatively simple.
 */
SymbolTable::SymbolTable(SymbolTable *p) {
	this->parent = p;
}

/*
 * Just a wrapper function for nesting scopes.
 */
void SymbolTable::add_sub_table(SymbolTable *k) {
	this->kids.push_back(k);
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

bool SymbolTable::empty() {
	for(std::size_t i = 0; i < this->HASHTABLE_SIZE; ++i) {
		if(!this->bucket[i].empty())
			return false;
	}
	return true;
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
 * Tries to get the symbol from the current scope.  If get_symbol throws an
 * ENoSymbolEntry, then the current scope doesn't have the symbol that is
 * being search for.  If the parent symbol table is NULL then we have reached
 * the global symbol table and the symbol doesn't exist so throw
 * ENoSymbolEntry again and let the calling function handle the exception. If
 * the symbol is found, it's returned.
 */
AbstractSymbol SymbolTable::get_scoped_symbol(std::string name) {
	try {
		AbstractSymbol symb = this->get_symbol(name);
		return symb;
	} catch(ENoSymbolEntry e) {
		if(this->parent == NULL) {
			throw ENoSymbolEntry();
		} else {
			this->parent->get_scoped_symbol(name);
		}
	}
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

void SymbolTable::print_table(std::size_t depth) {
	std::clog << this->to_string(depth) << std::endl;
}

std::string SymbolTable::to_string(std::size_t depth) {
	std::stringstream ss;
	for(std::size_t i = 0; i < this->HASHTABLE_SIZE; ++i) {
		std::deque<AbstractSymbol> b = this->bucket[i];
		std::deque<AbstractSymbol>::iterator it;
		for(it = b.begin(); it != b.end(); ++it) {
			ss << it->to_string(depth) << std::endl;
		}
	}
	return ss.str();
}

/* Basic Symbol constructor */
BasicSymbol::BasicSymbol(std::string n, std::string t, bool p)
				: AbstractSymbol(n,t), pointer(p) { }

/* Function symbol constructor */
FunctionSymbol::FunctionSymbol(std::string n, std::string t, bool p, bool d)
				: AbstractSymbol(n,t), pointer(p),
				def_needed(d) { }

std::string FunctionSymbol::to_string(std::size_t depth) {
	std::stringstream ss;
	ss << AbstractSymbol::to_string(depth) << std::endl;
	ss << this->params.to_string(depth+1) << std::endl;
	ss << this->locals.to_string(depth+1) << std::endl;
	return ss.str();
}