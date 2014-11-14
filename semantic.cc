/* semantic.cc
 * Semantic Analyzer Driver class to store all the parse trees and 
 * symbol tables.  Also is the class responsible for parsing the trees
 * and populating the symbol tables.
 * 
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#include <cstddef>
#include <iostream>

#include "120rules.hh"
#include "semantic.hh"

void SemanticAnalyzer::add_tree(TreeNode *r, TypenameTable e) {
	this->tuples.push_back(boost::make_tuple(r,new SymbolTable(),e));
}

/* 
 * Generate all of the symbols tables by iterating through each
 * parse tree and creating a symbol table from it.
 */
void SemanticAnalyzer::generate_all_tables() {
	std::deque< 
		boost::tuple<TreeNode*,SymbolTable*,TypenameTable> 
		>::iterator it;
	for(it = this->tuples.begin(); it != this->tuples.end(); ++it) {
		std::size_t i = it - this->tuples.begin();

		TreeNode *t(this->tuples[i].get<0>());
		SymbolTable *s(this->tuples[i].get<1>());
		TypenameTable &e(this->tuples[i].get<2>());
		this->generate_table(t,s,e);
	}
}

/*
 * Parse the parse tree in a pre-order traversal, identifying and creating
 * all symbols along the way and populating the proper symbol table.
 */
void SemanticAnalyzer::generate_table(TreeNode *t, SymbolTable *s,
					TypenameTable &e) {
	switch(t->prod_num) {
		/* Basic Symbols */
		case SIMPLE_DECL_1:
			if(t->kids[1]->prod_num == INIT_DECL_1) {
				TreeNode *n = t->kids[1]->kids[0];
				std::string ts = t->kids[0]->t->get_text(); 
				this->add_basic_symbol(n, ts, s);
			}
			break;
		default:
			if(t->num_kids > 0) {
				for(int i = 0; i < t->num_kids; ++i) {
					if(t->kids[i] != NULL) { 
						this->generate_table(
							t->kids[i], s, e);
					}
				}
			}
			break;
	}
}

/*
 * Check the current symbol table to make sure a symbol hasn't already been
 * declared and if not then create a new symbol and add it to the table.
 */
void SemanticAnalyzer::add_basic_symbol(TreeNode *t, std::string str, 
							SymbolTable *s) {
	std::string n = t->t->get_text();
	BasicSymbol basic(n, str);
	if(s->insert(n, basic)) {
		std::cout << "'" << n << "' (" << str 
			<< ") added to table!" << std::endl;
	} else {
		std::cout << "'" << n << 
			"' already declared in the local scope" << std::endl;
		exit(3);
	}

}