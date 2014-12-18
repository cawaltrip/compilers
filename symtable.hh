/*
 * symtable.hh
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

#ifndef _SYMTABLE_HH_
#define _SYMTABLE_HH_

#include <cstddef>
#include <string>

#include "typename.hh"

/*
 * AbstractSymbol is the base class for the other symbols to inherit
 * from.  Allows for polymorphism to be used in defining the types of the
 * buckets in the hash table.  The comparison of symbols will still only
 * be based on the name, so comparison is possible.  Inherited classes
 * appear after the SymbolTable declaration because some of the inherited
 * classes use SymbolTable objects.
 */
class AbstractSymbol {
public:
	std::string name;
	TypenameEntry type;
	explicit AbstractSymbol(std::string n, TypenameEntry t);
	virtual std::string to_string(std::size_t depth = 0);
};

/*
 * Operator overloading to allow for direct comparison of objects.  This may
 * possibly want to be put in the .cc file.
 */
inline bool operator==(const AbstractSymbol &lhs, const std::string &rhs) { 
	return (lhs.name == rhs);
}
inline bool operator!=(const AbstractSymbol &lhs, const std::string &rhs) { 
	return !(lhs.name == rhs);
}
inline bool operator==(const AbstractSymbol &lhs, const AbstractSymbol &rhs) { 
	return (lhs == rhs.name);
}
inline bool operator!=(const AbstractSymbol &lhs, const AbstractSymbol &rhs) { 
	return !(lhs == rhs.name);
}

/*
 * The hash table for the symbols.  Uses deques as the buckets just like the
 * TypenameTable does.  The deque is of AbstractSymbol pointers because
 * code slicing occurs when using polymorphism without pointers in C++.  With
 * the use of pointers, the symbols can now be of any type.
 */
class SymbolTable {
private:
	static const size_t HASHTABLE_SIZE = 137;
	std::deque<AbstractSymbol*> bucket[HASHTABLE_SIZE];
	std::size_t hash(std::string name);
	bool symbol_exists(std::string n);
public:
	SymbolTable(SymbolTable *p = NULL); /* Default to NULL parent */

	SymbolTable *parent;

	bool insert(std::string n, AbstractSymbol *s); /* TODO: Make void */
	AbstractSymbol* search(std::string n); /* TODO: remove function */
	AbstractSymbol* get_symbol(std::string n);
	AbstractSymbol* get_scoped_symbol(std::string n);
	bool remove(std::string n);
	void print_table(std::size_t depth = 0); /* TODO: Do I need this? */
	bool empty();
	std::string to_string(std::size_t depth = 0);
};

/* 
 * Basic symbols such as int, char, object instanciations.
 */
class BasicSymbol : public AbstractSymbol {
public:
	bool pointer;
	BasicSymbol(std::string n, TypenameEntry t, bool p = false);
	std::string to_string(std::size_t depth = 0);
};

/*
 * Class symbols are class definitions.
 */
class ClassSymbol : public AbstractSymbol {
public:
	SymbolTable *priv;
	SymbolTable *pub;
	ClassSymbol(std::string n, TypenameEntry t);
	ClassSymbol(std::string n, TypenameEntry t,
				SymbolTable pr = NULL, SymbolTable pu = NULL);
	std::string to_string(std::size_t depth = 0);
};

/*
 * Function prototype AND function definitions.
 */
class FunctionSymbol : public AbstractSymbol {
public:
	bool pointer;
	bool defined;
	SymbolTable *params;
	SymbolTable *locals;
	FunctionSymbol(std::string n, TypenameEntry t, bool ptr = false,
							bool defined = false);
	FunctionSymbol(std::string n, TypenameEntry t,
				SymbolTable par, SymbolTable loc,
				bool ptr = false, bool defined = false);
	FunctionSymbol(std::string n, TypenameEntry t, SymbolTable *s, 
				bool ptr = false, bool defined = false);
	std::string to_string(std::size_t depth = 0);
};

/*
 * Array declarations.
 */
class ArraySymbol : public AbstractSymbol {
public:
	bool pointer;
	std::size_t max_elements;
	ArraySymbol(std::string n, TypenameEntry t, bool p = false,
							std::size_t e = 1);
	std::string to_string(std::size_t depth = 0);
};

#endif /* _SYMTABLE_HH_ */