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
	/* 
	 * Get each part of the production rule using integer division
	 * and modulo.
	 */
	std::size_t base_rule = t->prod_num / 1000;
	std::size_t rule_num = t->prod_num % 1000;

	switch(base_rule) {
		case SIMPLE_DECL_R:
			this->symbolize_simple_decl(t, s);
			break;
		/* 
		 * If no rule is matched, parse all of the children that exist.
		 */
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
		std::clog << "'" << n << "' (" << str 
			<< ") added to table!" << std::endl;
	} else {
		std::cerr << "'" << n << 
			"' has already been declared!" << std::endl;
		exit(3);
	}

}

/*
 * Parse a simple declaration and find all symbols that need to be added
 * and then add them to the symbol table.
 */
void SemanticAnalyzer::symbolize_simple_decl(TreeNode *t, SymbolTable *s) {
	std::string ts;
	switch(t->prod_num) {
		case SIMPLE_DECL_1:
			ts = t->kids[0]->t->get_text();
			switch(t->kids[1]->prod_num) {
				case INIT_DECL_1:
					this->symbolize_init_decl(
						t->kids[1]->kids[0], s, ts);
					break;
				case INIT_DECL_LIST_2:
					this->symbolize_init_decl_list(
						t->kids[1], s, ts);
					break;
			}
			break;
		case SIMPLE_DECL_2:
			std::clog << "SIMPLE_DECL_2 ???" << std::endl;
			break;
		default:
			break;
	}
}
void SemanticAnalyzer::symbolize_init_decl(TreeNode *t, SymbolTable *s, 
							std::string ident) {
	this->add_basic_symbol(t, ident, s);
}
void SemanticAnalyzer::symbolize_init_decl_list(TreeNode *t, SymbolTable *s,
							std::string ident) {
	
	/* Currently only adds the first of the list to the symbol table. */
	if(t->kids[0] != NULL) {
		if(t->kids[0]->prod_num == INIT_DECL_LIST_2) {
			std::cout << "Symbolizing init decl list" << std::endl;
			this->symbolize_init_decl_list(t->kids[0], s, ident);
		} else if(t->kids[0]->prod_num == INIT_DECL_1) {
			std::cout << "Symbolizing variable" << std::endl;
			this->symbolize_init_decl(t->kids[0]->kids[0], 
								s, ident);
		}
	}
}