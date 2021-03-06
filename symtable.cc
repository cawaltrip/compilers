/*
 * symtable.cc
 * UIdaho CS-445 120++ Compiler
 * Symbol Table class for storing of symbols for back-end compilation stages
 * 
 * Copyright (C) 2014 Chris Waltrip <walt2178@vandals.uidaho.edu>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <sstream>
#include <string>

#include "symtable.hh"
#include "exception.hh"


/* 
 * The only time that SymbolTable's parent will be NULL is the Global Symbol
 * Table.  Given this and the n-ary tree (represented using std::deque),
 * resolving scope should be relatively simple.
 */
SymbolTable::SymbolTable(SymbolTable *p) {
	this->parent = p;
}

/* This hashing method is identical to the Typename Table hash method */
std::size_t SymbolTable::hash(std::string name) {
	std::size_t hash = 0;
	const char* s = name.c_str();
	while(*s) {
		hash = hash * 101 + *s++;
	}
	return hash % this->HASHTABLE_SIZE;
}

bool SymbolTable::insert(std::string n, AbstractSymbol *s) {
	if(!this->symbol_exists(n)) {
		std::size_t h = this->hash(n);
		this->bucket[h].push_back(s);
		return true;
	}
	throw EDuplicateSymbol();
	return false; /* Remove after refactor */
}

bool SymbolTable::empty() {
	for(std::size_t i = 0; i < this->HASHTABLE_SIZE; ++i) {
		if(!this->bucket[i].empty())
			return false;
	}
	return true;
}

AbstractSymbol* SymbolTable::get_symbol(std::string name) {
	std::size_t h = this->hash(name);
	std::deque<AbstractSymbol*> b = this->bucket[h];
	std::deque<AbstractSymbol*>::iterator it;
	for(it = b.begin(); it != b.end(); ++it) {
		std::size_t i = it - b.begin();
		if(*(b[i]) == name) {
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
AbstractSymbol* SymbolTable::get_scoped_symbol(std::string name) {
	AbstractSymbol *symb;
	try {
		symb = this->get_symbol(name);
		return symb;
	} catch(ENoSymbolEntry e) {
		if(this->parent == NULL) {
			throw ENoSymbolEntry();
		} else {
			/* Will never be NULL because exception is thrown */
			return this->parent->get_scoped_symbol(name);
		}
	}
}

/*
 * Will return true if a symbol is found.  If get_symbol throws
 * an ENoSymbolEntry exception, then the symbol isn't in the symbol
 * table.  This only checks for the existance in the local symbol table.
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
	std::clog << this->to_string(depth);
}

std::string SymbolTable::to_string(std::size_t depth) {
	std::stringstream ss;
	for(std::size_t i = 0; i < this->HASHTABLE_SIZE; ++i) {
		std::deque<AbstractSymbol*> b = this->bucket[i];
		std::deque<AbstractSymbol*>::iterator it;
		for(it = b.begin(); it != b.end(); ++it) {
			ss << (*it)->to_string(depth);
		}
	}
	return ss.str();
}

/* Symbol constructors */
AbstractSymbol::AbstractSymbol(std::string n, TypenameEntry t)
			: name(n), type(t) { }
BasicSymbol::BasicSymbol(std::string n, TypenameEntry t, bool p)
				: AbstractSymbol(n,t), pointer(p) { }
FunctionSymbol::FunctionSymbol(std::string n, TypenameEntry t, bool p, bool d)
				: AbstractSymbol(n,t), pointer(p), defined(d) {
	this->locals = new SymbolTable();
	this->params = new SymbolTable(); 
}
FunctionSymbol::FunctionSymbol(std::string n, TypenameEntry t, SymbolTable *s, 
				bool p, bool d)
				: AbstractSymbol(n,t), pointer(p), defined(d) {
	this->locals = new SymbolTable(s);
	this->params = new SymbolTable(s);
}
ArraySymbol::ArraySymbol(std::string n, TypenameEntry t, bool p, std::size_t e) 
				: AbstractSymbol(n,t),
				pointer(p), max_elements(e) { }
ClassSymbol::ClassSymbol(std::string n, TypenameEntry t) : AbstractSymbol(n,t) {
	this->priv = new SymbolTable();
	this->pub = new SymbolTable();
}


/* String representation of symbols */
std::string AbstractSymbol::to_string(std::size_t depth) {
	std::string spaces = std::string(depth, '>');
	std::stringstream ss;
	ss << spaces << this->type << " " << this->name << std::endl;
	return ss.str();
}
std::string BasicSymbol::to_string(std::size_t depth) {
	std::stringstream ss;
	if(this->pointer) {
		ss << "(pointer) ";
	}
	ss << AbstractSymbol::to_string(depth);
	return ss.str();
}
std::string FunctionSymbol::to_string(std::size_t depth) {
	std::stringstream ss;
	if(this->pointer) {
		ss << "(pointer) ";
	}
	ss << AbstractSymbol::to_string(depth);
		if(this->params != NULL) {
			ss << this->params->to_string(depth+1);
		}
		if(this->locals != NULL) {
			ss << this->locals->to_string(depth+1);	
		}
	return ss.str();
}
std::string ArraySymbol::to_string(std::size_t depth) {
	std::stringstream ss;
	if(this->pointer) {
		ss << "(pointer) ";
	}
	ss << "[" << this->max_elements << "] ";
	ss << AbstractSymbol::to_string(depth);
	return ss.str();
}
std::string ClassSymbol::to_string(std::size_t depth) {
	std::stringstream ss;
	ss << AbstractSymbol::to_string(depth);
	ss << this->priv->to_string(depth+1);
	ss << this->pub->to_string(depth+1);
	return ss.str();
}