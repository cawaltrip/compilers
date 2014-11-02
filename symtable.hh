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
#include <boost/variant.hpp>

#include "symbols.hh"
#include "typename.hh"

/*
 * Variant representing the different types of possible symbols
 */
typedef boost::variant<BasicSymbol, ClassSymbol, FuncSymbol, ArraySymbol> 
	SymbolVariant;

/*
 * Symbol wrapper that will store the symbol variant.
 */
class Symbol {
private:
	TypenameEntry entry;
	SymbolVariant symb;
public:
	Symbol(TypenameEntry e, SymbolVariant s);
	std::string &name;
};

inline bool operator==(const Symbol& lhs, const std::string& rhs) { 
	return (lhs.name == rhs);
}
inline bool operator!=(const Symbol& lhs, const std::string& rhs) { 
	return !(lhs.name == rhs);
}
inline bool operator==(const Symbol& lhs, const Symbol& rhs) { 
	return (lhs == rhs.name);
}
inline bool operator!=(const Symbol& lhs, const Symbol& rhs) { 
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
	std::deque<Symbol> bucket[HASHTABLE_SIZE];
	std::size_t hash(std::string name);
public:
	bool insert(std::string n, Symbol s);
	Symbol search(std::string n);
	Symbol get_symbol(std::string n);
	bool remove(std::string n);
};

#endif /* _SYMTABLE_HH_ */