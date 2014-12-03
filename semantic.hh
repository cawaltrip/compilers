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

#include <cstddef>
#include <deque>
#include <boost/tuple/tuple.hpp>

#include "symtable.hh"
#include "treenode.hh"

/* 
 * The SemanticAnalyzer holds a list of all the parse trees and the 
 * symbol tables created from them.  Each rule that has a symbol table or
 * needs to have type checking applied to it will have their own functions.
 * The result is a lot of functions with similar (but different) logic and the
 * main switch statement that parses the trees is easier to follow.
 */
class SemanticAnalyzer {
private:
	std::deque< boost::tuple<TreeNode*,SymbolTable*,TypenameTable> > tuples;
	void generate_table(TreeNode *t, SymbolTable *s, TypenameTable &e); /* Driver for creating the individual table */
	void print_table(SymbolTable *s, std::size_t depth);

	/* Functions that adds a symbol to the symbol table */
	void add_symbol(AbstractSymbol *a, SymbolTable *s);
	void add_basic_symbol(TreeNode *t, SymbolTable *s, std::string str);

	/* Functions that create a symbol to add to the symbol table */
	void symbolize_init_decl(TreeNode *t, SymbolTable *s, std::string type);
	void symbolize_param_decl(TreeNode *t, SymbolTable *s);
	void symbolize_function_prototype(TreeNode *t, SymbolTable *s,
							std::string type);

	/* All of the different rule parsers */
	void symbolize_simple_decl(TreeNode *t, SymbolTable *s);
	void symbolize_init_decl_list(TreeNode *t, SymbolTable *s, 
							std::string id);
	void symbolize_param_decl_list(TreeNode *t, SymbolTable *s);
public:
	void add_tree(TreeNode *root, TypenameTable table);
	void generate_all_tables(); /* Iterates through all pairs to populate all tables */
	void print_all_tables();
};

#endif /* _SEMANTIC_HH_ */