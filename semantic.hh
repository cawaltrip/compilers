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
#include <boost/tuple/tuple.hpp>

#include "symtable.hh"
#include "treenode.hh"

/* 
 * The SemanticAnalyzer holds a list of all the parse trees and the 
 * symbol tables created from them.
 */
class SemanticAnalyzer {
private:
	std::deque< boost::tuple<TreeNode*,SymbolTable,TypenameTable> > tuples;
	void generate_table(TreeNode *t, SymbolTable &s, TypenameTable &e); /* Driver for creating the individual table */
	void symbolize_node(TreeNode *t, SymbolTable &s, TypenameTable &e); /* Performs actions based on what production rule is seen. */
public:
	void add_tree(TreeNode *root, TypenameTable table); /* Instanciates an empty gst with it? */
	void generate_all_tables(); /* Iterates through all pairs to populate all tables */
};

#endif /* _SEMANTIC_HH_ */