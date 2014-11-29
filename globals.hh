/* globals.hh
 * Semantic Analyzer Driver class to store all the parse trees and 
 * symbol tables.  Also is the class responsible for parsing the trees
 * and populating the symbol tables.
 * 
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#ifndef _GLOBALS_HH_
#define _GLOBALS_HH_

/* Read-only flags */
static bool FULL_PARSE_TREES = false;
static bool PRINT_PARSE_TREES = true;

/* Global writable flags */
static bool PARSE_ERROR = false;

/* Custom exit status codes */
static const unsigned short EXIT_LEXICAL_ERROR = 1;
static const unsigned short EXIT_SYNTAX_ERROR = 2;
static const unsigned short EXIT_SEMANTIC_ERROR = 3;
static const unsigned short EXIT_UNSUPPORTED = 4;


#endif /* _GLOBALS_HH_ */