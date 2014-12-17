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
#include <typeinfo>

#include "120rules.hh"
#include "exception.hh"
#include "globals.hh"
#include "semantic.hh"
#include "treenode.hh"


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

		std::clog << "Generating table number " << i << ": ";
		std::clog << std::endl;

		TreeNode *t(this->tuples[i].get<0>());
		SymbolTable *s(this->tuples[i].get<1>());
		TypenameTable &e(this->tuples[i].get<2>());
		this->generate_table(t,s,e);
	}
}

/*
 * Iterate through each of the tuples and print the symbol tables from each
 * of them.
 */
void SemanticAnalyzer::print_all_tables() {
	std::deque< 
		boost::tuple<TreeNode*,SymbolTable*,TypenameTable> 
		>::iterator it;
	for(it = this->tuples.begin(); it != this->tuples.end(); ++it) {
		std::size_t i = it - this->tuples.begin();

		std::clog << "Printing symbol table #" << i << std::endl;
		std::clog << "===================================" << std::endl;

		this->tuples[i].get<1>()->print_table();

		std::clog << std::endl;
	}
}

void SemanticAnalyzer::print_all_trees() {
	std::deque< 
		boost::tuple<TreeNode*,SymbolTable*,TypenameTable> 
		>::iterator it;
	for(it = this->tuples.begin(); it != this->tuples.end(); ++it) {
		std::size_t i = it - this->tuples.begin();

		std::clog << "Printing tree #" << i << std::endl;
		std::clog << "===================================" << std::endl;

		print_tree(this->tuples[i].get<0>());

		std::clog << std::endl;
	}
}

/*
 * Parse the parse tree in a pre-order traversal, identifying and creating
 * all symbols along the way and populating the proper symbol table.
 */
void SemanticAnalyzer::generate_table(TreeNode *t, SymbolTable *s, 
							TypenameTable &e) {
	try {
		switch(t->prod_num) {
			case SIMPLE_DECL_1:
				this->symbolize_simple_decl(t, s, e);
				break;
			case FUNC_DECL_2:
				this->symbolize_function_def(t,s, e);
				break;
			/* 
			 * If no rule is matched, parse all of the children 
			 * that exist.
			 */
			default:
				//if(t->num_kids > 0) { /* Not sure I need this */
				for(int i = 0; i < t->num_kids; ++i) {
					if(node_exists(t->kids[i])) { 
						this->generate_table(
							t->kids[i], s, e);
					}
				}
				//}
				break;
		}	
	} catch (ESymbolTableNestedTooDeep e) { /* Won't ever be thrown */
		std::cerr << e.what() << std::endl;
		exit(EXIT_SEMANTIC_ERROR);
	} catch (EBadGrammarParse e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_SEMANTIC_ERROR);
	}
	
}

/*
 * After a symbol has been built, attempt to insert it into the symbol table.
 * If the symbol already exists, EDuplicateSymbol is thrown.  Report an error
 * an then throw the same exception if this occurs.  This allows the calling
 * function to decide to keep running or exit on a per-case basis.  Right now, 
 * this function exits the compiler before this throw happens because I don't
 * have a case where I don't want to exit on a duplicate symbol.
 */
void SemanticAnalyzer::add_symbol(AbstractSymbol *a, SymbolTable *s) {
	try {
		s->insert(a->name,a);
	} catch (EDuplicateSymbol e) {
		std::cerr << e.what() << ": " << a->name << std::endl;
		exit(EXIT_SEMANTIC_ERROR);
		throw EDuplicateSymbol(); /* Never reached, maybe future use */
	}
	std::clog << "'" << a->name << "' (" << a->type << ") added to table!";
	std::clog << std::endl;
}

/*
 * Create a wrapper around getting the symbol from the symbol table.
 */
AbstractSymbol* SemanticAnalyzer::get_symbol(AbstractSymbol *a,
							SymbolTable *s) {
	return this->get_symbol(a->name, s);
}
AbstractSymbol* SemanticAnalyzer::get_symbol(std::string name,
							SymbolTable *s) {
	AbstractSymbol* symb;
	try {
		symb = s->get_symbol(name);
	} catch (ENoSymbolEntry e) {
		throw ENoSymbolEntry();
	}
	return symb;
}

/*
 * Check the current symbol table to make sure a symbol hasn't already been
 * declared and if not then create a new symbol and add it to the table.
 *
 * TODO: Remove this and move to the functions that call this??
 */
void SemanticAnalyzer::add_basic_symbol(TreeNode *t, SymbolTable *s,
					TypenameEntry e, bool is_pointer) {
	if(t->t != NULL) {
		std::string n = t->t->get_text();
		BasicSymbol *basic = new BasicSymbol(n, e, is_pointer);
		this->add_symbol(basic, s); /* Will exit if exception thrown */
		
		/*
		 * If no exception was thrown then set SymbolTable* in TreeNode
		 * to be the current symbol table so that we can access it
		 * during type checking.
		 */
		t->s = s;
	} else {
		throw ENullTokenAccess();
	}
}

/*
 * Parse a simple declaration and find all symbols that need to be added
 * and then add them to the symbol table.
 *
 * A simple declarator will either be an initialization list or a
 * class/function initialization.
 */
void SemanticAnalyzer::symbolize_simple_decl(TreeNode *t, SymbolTable *s,
							TypenameTable e) {
	switch(t->prod_num) {
		case SIMPLE_DECL_1:
			//e.get_entry(t->kids[0]->t->get_text());
			switch(t->kids[1]->prod_num) {
				case INIT_DECL_1:
					this->symbolize_init_decl(
						t->kids[1], s, e, e.get_entry(t->kids[0]->t->get_text()));
					break;
				case INIT_DECL_LIST_2:
					this->symbolize_init_decl_list(
						t->kids[1], s, e, e.get_entry(t->kids[0]->t->get_text()));
					break;
			}
		default:
			break;
	}
}
/*
 * Initialization declarations include basic variable declarations as well as
 * function prototypes.  Parse the subtree and identify the type of declaration
 * and add the necessary symbols to the symbol table.
 */
void SemanticAnalyzer::symbolize_init_decl(TreeNode *t, SymbolTable *s,
					TypenameTable e, TypenameEntry type,
					bool ptr) {

	std::size_t i = 0;
	//bool ptr = false;
	
	/* Make sure parse tree isn't destroyed */
	TreeNode *x = t;

	/* Check and adjust for pointer */
	if(x->kids[0]->prod_num == DECLARATOR_2) {
		ptr = true;
		++i;
		x = t->kids[0];
	}

	/* Now that pointer's been determined, handle the init-decl */
	/* Basic Symbol */
	if(is_token(x->kids[i])) {
		try {
			this->add_basic_symbol(x->kids[i], s, type, ptr);
			return;
		} catch (ENullTokenAccess ex) {
			std::cerr << ex.what() << std::endl;
			exit(EXIT_SEMANTIC_ERROR);
		}
	}

	/* 
	 * Wasn't a basic symbol.  Check for function prototype -- function
	 * definitions are handled in different parent node.  No need to handle
	 * here.
	 *
	 * Also check for arrays
	 */
	if(x->kids[i]->prod_num == DIRECT_DECL_5) {
		this->symbolize_function_prototype(x->kids[i], s, e, type, ptr);
		return;
	} else if(x->kids[i]->prod_num == DIRECT_DECL_6) {
		this->symbolize_array(x->kids[i], s, type, ptr);
		return;
	}

	/* Undefined parse reached */
	std::clog << "Undefined parse reached. ";
	std::clog << "Current node: " << single_node_string(x) << std::endl;
	std::clog << "Remaining subtree: " << std::endl;
	print_tree(x);
	std::clog << std::endl;
	throw EBadGrammarParse();
}

/*
 * An init-decl-list can be either the variable name itself or could be
 * something like a function that we need to dig further down into.
 */
void SemanticAnalyzer::symbolize_init_decl_list(TreeNode *t, SymbolTable *s,
							TypenameTable e,
							TypenameEntry type) {
	for(std::size_t i = 0; i < t->num_kids; ++i) {
		if(node_exists(t->kids[i])) {
			switch(t->kids[i]->prod_num) {
				case INIT_DECL_LIST_2:
					this->symbolize_init_decl_list(
							t->kids[i], s, e, type);
					break;
				case INIT_DECL_1:
					this->symbolize_init_decl(
							t->kids[i], s, e, type);
					break;
			}
		}
	}
}

/*
 * Parameter declarations are similar (if not identical) to initialization 
 * declarations.
 */
void SemanticAnalyzer::symbolize_param_decl(TreeNode *t, SymbolTable *s,
							TypenameTable e) {
	TypenameEntry type = e.get_entry(t->kids[0]->t->get_text());
	this->add_basic_symbol(t->kids[1], s, type);
}

/*
 * Parameter declaration lists are similar (if not identical) to initialization
 * declaration lists.
 */
void SemanticAnalyzer::symbolize_param_decl_list(TreeNode *t,
							SymbolTable *s,
							TypenameTable e) {
	for(std::size_t i = 0; i < t->num_kids; ++i) {
		if(node_exists(t->kids[i])) {
			switch(t->kids[i]->prod_num) {
				case PARAM_DECL_LIST_2:
					this->symbolize_param_decl_list(
							t->kids[i], s, e);
					break;
				case PARAM_DECL_1:
					this->symbolize_param_decl(
							t->kids[i], s, e);
					break;
			}
		}
	}
}

/*
 * Function prototypes are defined in DIRECT_DECL_5.  This also adds a function
 * symbol to the symbol table.
 *
 * kids[0] <-- function name
 * kids[2] <-- possible parameter list
 */
FunctionSymbol* SemanticAnalyzer::symbolize_function_prototype(TreeNode *t,
							SymbolTable *s,
							TypenameTable e,
							TypenameEntry type, 
							bool is_pointer) {
	std::string n = t->kids[0]->t->get_text();
	FunctionSymbol *func = new FunctionSymbol(n, type, is_pointer);
	this->add_symbol(func,s);
	t->kids[0]->s = s;
	/* Parse parameter list if it exists */
	if(node_exists(t->kids[2])) {	
		SymbolTable *p = new SymbolTable(s);
		switch(t->kids[2]->prod_num) {
			case PARAM_DECL_LIST_2:
				this->symbolize_param_decl_list(
							t->kids[2], p, e);
				break;
			case PARAM_DECL_1:
				this->symbolize_param_decl(t->kids[2], p, e);
				break;
			default:
				throw EBadGrammarParse();
				break;
		}
		func->params = p;
	}
	return func;
}

/*
 * Function definitions only need the locals symbol table (type checking is
 * where the parameters will need to be checked).  
 *
 * Nested functions are implicitly allowed in this code, however the syntax
 * checking would flag those and so it's not a problem.
 */
void SemanticAnalyzer::symbolize_function_def(TreeNode *t, SymbolTable *s,
						TypenameTable e, bool ptr) {
	
	/* Use a special copy of the tree in case a pointer exists */
	TreeNode *x = t;

	/* Check and adjust for pointer */
	if(x->kids[1]->prod_num == DECLARATOR_2) {
		ptr = true;
		x = t->kids[1]->kids[1]; /* TreeNode for direct declarator */
	} else {
		x = t->kids[1];
	}

	FunctionSymbol *f;
	std::string name = x->kids[0]->t->get_text();

	try {
		AbstractSymbol *tmp = this->get_symbol(name,s);
		f = dynamic_cast<FunctionSymbol*>(tmp);
	} catch (ENoSymbolEntry ex) {
		TypenameEntry type = e.get_entry(t->kids[0]->t->get_text());
		f = this->symbolize_function_prototype(x, s, e, type, ptr);
	} catch (const std::bad_cast& ex) {
		std::cerr << ex.what() << std::endl;
		std::cerr << "symbol declared as non-function" << std::endl;
		return;
	}
	
	/* Fake the TypenameTable for now because I'm not using it */
	this->generate_table(t->kids[3], f->locals, e);
}

/*
 * Array symbols are similar to other types of symbols except that they fall
 * under DIRECT-DECL-6 and have some sort of integer inside the square
 * brackets.  This function will also do type checking on the inside to make
 * sure that it can even be added as a symbol -- that is, make sure that the
 * number of elements is actually an integer.
 */
void SemanticAnalyzer::symbolize_array(TreeNode *t, SymbolTable *s,
						TypenameEntry e, bool ptr) {
	std::string name = t->kids[0]->t->get_text();
	std::size_t elems = t->kids[2]->t->get_ival();

	ArraySymbol *a = new ArraySymbol(name, e, ptr, elems);
	this->add_symbol(a,s);
	t->kids[0]->s = s;
	return;
}
