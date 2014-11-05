/* semantic.cc
 * Semantic Analyzer Driver class to store all the parse trees and 
 * symbol tables.  Also is the class responsible for parsing the trees
 * and populating the symbol tables.
 * 
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#include <cstddef>

#include "120rules.hh"
#include "semantic.hh"

void SemanticAnalyzer::add_tree(TreeNode *r, TypenameTable e) {
	this->tuples.push_back(boost::make_tuple(r,SymbolTable(),e));
}

/* 
 * Generate all of the symbols tables by iterating through each
 * parse tree and creating a symbol table from it.
 */
void SemanticAnalyzer::generate_all_tables() {
	std::deque< 
		boost::tuple<TreeNode*,SymbolTable,TypenameTable> 
		>::iterator it;
	for(it = this->tuples.begin(); it != this->tuples.end(); ++it) {
		std::size_t i = it - this->tuples.begin();

		TreeNode *t(this->tuples[i].get<0>());
		SymbolTable &s(this->tuples[i].get<1>());
		TypenameTable &e(this->tuples[i].get<2>());
		this->generate_table(t,s,e);
	}
}

/*
 * Parse the parse tree in a pre-order traversal, identifying and creating
 * all symbols along the way and populating the proper symbol table.
 */
void SemanticAnalyzer::generate_table(TreeNode *t, SymbolTable &s,
					TypenameTable &e) {
	switch(t->prod_num) {
		/* Basic Symbols */
		case SIMPLE_DECL_1:
			break;
	}
}

/*
 * Contains the different cases for what the production rule could be and
 * creates the symbol(s) for the symbol table.
 */
void SemanticAnalyzer::symbolize_node(TreeNode *t, SymbolTable &s,
					TypenameTable &e) {

}