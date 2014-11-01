/* symbols.hh
 * Symbol prototypes for the different types of symbols that will be added to
 * the symbol table.
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#ifndef _SYMBOLS_HH_
#define _SYMBOLS_HH_

#include <string>
#include <boost/variant.hpp>

#include "typename.hh"

typedef struct BasicSymbol {

} BSymb;

typedef struct ClassSymbol {

} CSymb;

typedef struct FunctionSymbol {

} FSymb;

typedef struct ArraySymbol {

} ASymb;

class Symbol {
private:
	TypenameEntry entry;
	boost::variant<BSymb, CSymb, FSymb, ASymb> symb;
public:
	Symbol(TypenameEntry e, boost::variant<BSymb, CSymb, FSymb, ASymb> s);
	std::string name;
};



#endif /* _SYMBOLS_HH_ */