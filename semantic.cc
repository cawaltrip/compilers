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

void SemanticAnalyzer::add_tree(TreeNode r) {
	this->pairs.push_back(std::make_pair(r,SymbolTable()));
}

/* 
 * Generate all of the symbols tables by iterating through each
 * parse tree and creating a symbol table from it.
 */
void SemanticAnalyzer::generate_all_tables() {
	std::deque< std::pair<TreeNode,SymbolTable> >::iterator it;
	for(it = this->pairs.begin(); it != this->pairs.end(); ++it) {
		std::size_t i = it - this->pairs.begin();
		//std::pair<TreeNode,SymbolTable> &p(this->pairs[i]);
		TreeNode &t(this->pairs[i].first);
		SymbolTable &s(this->pairs[i].second);

		this->generate_table(t,s);
	}
}

/*
 * Parse the parse tree in a pre-order traversal, identifying and creating
 * all symbols along the way and populating the proper symbol table.
 */
void SemanticAnalyzer::generate_table(TreeNode &t, SymbolTable &s) {

}

/*
 * Contains the different cases for what the production rule could be and
 * creates the symbol(s) for the symbol table.  Because the production rule
 * numbers and text are contained in individual structs instead of statically
 * declared, if-else-if statements need to be used instead of a switch
 * statement.  It would be a good idea to change how this is done.
 */
void SemanticAnalyzer::symbolize_node(TreeNode &t, SymbolTable &s) {
	

	switch(t.prod_num) {
		case START_RULE:
			std::cout << "Start rule seen??" << std::endl;
			break;
		default:
			break;
	}
}