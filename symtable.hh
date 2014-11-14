/* symtable.hh
 * Hash table representing the symbol table.
 * the symbol table.
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
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
	std::string type_string;
	//TypenameEntry type;
	//explicit AbstractSymbol(std::string n, TypenameEntry t);
	explicit AbstractSymbol(std::string n, std::string t);
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
 * TypenameTable does.
 *
 * TODO: Combine SymbolTable and TypenameTable into a templated hash table if
 *	 possible.
 */
class SymbolTable {
private:
	static const size_t HASHTABLE_SIZE = 137;
	std::deque<AbstractSymbol> bucket[HASHTABLE_SIZE];
	std::size_t hash(std::string name);
	bool symbol_exists(std::string n);
	SymbolTable *parent;
public:
	SymbolTable(SymbolTable *p = NULL);
	std::deque<SymbolTable*> kids;
	void add_sub_table(SymbolTable *k);
	bool insert(std::string n, AbstractSymbol s);
	AbstractSymbol search(std::string n);
	AbstractSymbol get_symbol(std::string n);
	bool remove(std::string n);
};

/* 
 * Basic symbols such as int, char, object instanciations.
 */
class BasicSymbol : public AbstractSymbol {
public:
	bool pointer;
	BasicSymbol(std::string n, std::string t, bool p = false);
};

/*
 * Class symbols are class definitions.
 */
class ClassSymbol : public AbstractSymbol {
	SymbolTable priv;
	SymbolTable pub;
	ClassSymbol(std::string n, std::string t);
	ClassSymbol(std::string n, std::string t,
				SymbolTable pr, SymbolTable pu);
};

/*
 * Function prototype AND function definitions.
 */
class FunctionSymbol : public AbstractSymbol {
	bool pointer;
	bool def_needed;
	SymbolTable params;
	SymbolTable locals;
	FunctionSymbol(std::string n, std::string t,
				bool ptr = false, bool def = false);
	FunctionSymbol(std::string n, std::string t,
				SymbolTable par, SymbolTable loc,
				bool ptr = false, bool def = false);
};

/*
 * Array declarations.
 */
class ArraySymbol : public AbstractSymbol {
	bool pointer;
	std::size_t max_elements;
	ArraySymbol(std::string n, std::string t,
				bool p = false, std::size_t e = 1);
};

#endif /* _SYMTABLE_HH_ */