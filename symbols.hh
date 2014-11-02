/* symbols.hh
 * Symbol prototypes for the different types of symbols that will be added to
 * the symbol table.
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#ifndef _SYMBOLS_HH_
#define _SYMBOLS_HH_

#include <cstddef>
#include <string>
#include <boost/variant.hpp>

#include "typename.hh"

typedef struct BasicSymbol {
	bool pointer;
} BasicSymbol;

typedef struct ClassSymbol {

} ClassSymbol;

typedef struct FuncSymbol {
	bool pointer;
	bool definition_needed;
} FuncSymbol;

typedef struct ArraySymbol {
	bool pointer;
	size_t max_elements;
} ArraySymbol;



#endif /* _SYMBOLS_HH_ */