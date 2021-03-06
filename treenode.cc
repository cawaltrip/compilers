/*
 * treenode.cc
 * UIdaho CS-445 120++ Compiler
 * Helper functions for abstract syntax tree nodes
 * 
 * Copyright (C) 2014 Chris Waltrip <walt2178@vandals.uidaho.edu>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <iostream>
#include <sstream>
#include "treenode.hh"
#include "token.hh"
#include "120gram.tab.h"

/* Simple wrapper functions for commonly checked node status */
bool is_leaf(struct TreeNode *t) {
	return !(t->num_kids);
}

bool is_token(struct TreeNode *t) {
	if(t->t != NULL) {
		return true;
	}
	return false;
}

bool node_exists(struct TreeNode *t) {
	if(t != NULL) {
		return true;
	}
	return false;
}

bool has_symbol_table(struct TreeNode *t) {
	return (t->s != NULL);
}

bool has_symbol(struct TreeNode *t) {
	return (t->a != NULL);
}

bool is_identifier(struct TreeNode *t) {
	if(is_token(t)) {
		if(t->t->get_category() == IDENTIFIER) {
			return true;
		}
	}
	return false;
}

/* 
 * Stolen and modified from Dr. J's CS-445 HW2 Notes:
 * 	http://www2.cs.uidaho.edu/~jeffery/courses/445/hw2.html
 * If the node has no kids then it's a leaf and leaf nodes are just tokens.
 */
void print_tree(struct TreeNode *t, int depth) {
	std::stringstream s;
	std::string spaces = std::string(depth*2, ' ');

	s << spaces;

	if(is_leaf(t)) {
		s << t->t->get_category() << ": " << t->t->get_text();
	} else {
		s << t->prod_text;
		s << " (" << t->prod_num << "," << t->num_kids << ")";
	}
	std::cout << s.str() << std::endl;

	for(int i=0; i<t->num_kids; ++i)
		if(t->kids[i] != NULL)
			print_tree(t->kids[i], depth+1);
}
void print_symbol(struct TreeNode *t) {
	if(is_leaf(t)) {
		int cat = t->t->get_category();
		if(cat == IDENTIFIER) {
			std::cout << t->t->get_text() << std::endl;
		}
	}
	for (int i=0; i<t->num_kids; ++i) {
		if(node_exists(t->kids[i])) {
			print_symbol(t->kids[i]);
		}
	}
}

std::string single_node_string(TreeNode *t) {
	std::stringstream ss;
	if(is_token(t)) {
		ss << t->t->get_text();
	} else {
		ss << t->prod_text;
	}
	return ss.str();
}