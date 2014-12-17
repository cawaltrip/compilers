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
	void generate_table(TreeNode *t, SymbolTable *s, TypenameTable &e);
	void check_tree(TreeNode *t);
	void print_table(SymbolTable *s, std::size_t depth);
	AbstractSymbol* get_symbol(AbstractSymbol *a, SymbolTable *s,
					TypenameTable e);
	AbstractSymbol* get_symbol(std::string name, SymbolTable *s,
					TypenameTable e);

	/* SymbolTable population */
	void add_symbol(AbstractSymbol *a, SymbolTable *s);
	void add_basic_symbol(TreeNode *t, SymbolTable *s, TypenameEntry type,
					bool ptr = false);
	void symbolize_init_decl(TreeNode *t, SymbolTable *s, TypenameTable e,
					TypenameEntry type, bool ptr = false);
	void symbolize_array(TreeNode *t, SymbolTable *s,
					TypenameEntry type, bool ptr = false);
	void symbolize_function_def(TreeNode *t, SymbolTable *s,
					TypenameTable e, bool ptr = false);
	FunctionSymbol* symbolize_function_prototype(TreeNode *t,
					SymbolTable *s, TypenameTable e,
					TypenameEntry type, bool ptr = false);
	void symbolize_init_decl_list(TreeNode *t, SymbolTable *s,
					TypenameTable e, TypenameEntry type);
	void symbolize_param_decl(TreeNode *t, SymbolTable *s, TypenameTable e);
	void symbolize_param_decl_list(TreeNode *t, SymbolTable *s,
							TypenameTable e);
	void symbolize_simple_decl(TreeNode *t, SymbolTable *s,
					TypenameTable e);

	/* Type checking */

public:
	void add_tree(TreeNode *root, TypenameTable table);
	void generate_all_tables();
	void check_all();
	void print_all_tables();
	void print_all_trees();
};

#endif /* _SEMANTIC_HH_ */