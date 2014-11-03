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
static const bool FULL_PARSE_TREES = true;
static const bool PRINT_PARSE_TREES = true;

/* Global writable flags */
static bool PARSE_ERROR = false;


#endif /* _GLOBALS_HH_ */