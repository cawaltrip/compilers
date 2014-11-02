/* semantic.hh
 * Semantic Analyzer Driver class to store all the parse trees and 
 * symbol tables.  Also is the class responsible for parsing the trees
 * and populating the symbol tables.
 * 
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#ifndef _SEMANTIC_HH_
#define _SEMANTIC_HH_

#include <deque>
#include <utility>

#include "symtable.hh"
#include "treenode.hh"

/* 
 * The SemanticAnalyzer holds a list of all the parse trees and the 
 * symbol tables created from them.
 */
class SemanticAnalyzer {
private:
	std::deque< std::pair<TreeNode,SymbolTable> > pairs;
	void generate_table(TreeNode &t, SymbolTable &s); /* Driver for creating the individual table */
public:
	void add_tree(TreeNode root); /* Instanciates an empty gst with it? */
	void generate_all_tables(); /* Iterates through all pairs to populate all tables */
};

#endif /* _SEMANTIC_HH_ */