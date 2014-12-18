/*
 * treenode.hh
 * UIdaho CS-445 120++ Compiler
 * Abstract syntax tree data structure for 120++ compiler
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

#ifndef _TREENODE_HH_
#define _TREENODE_HH_

#include <string>
#include "symtable.hh"
#include "token.hh"

/* TODO: Dynamically allocate kids */
struct TreeNode {
	static const std::size_t MAX_KIDS = 10;
	int prod_num;
	std::string prod_text;
	int num_kids;
	struct TreeNode *kids[MAX_KIDS];
	Token *t;
	SymbolTable *s;
};

bool is_leaf(struct TreeNode *t);
bool is_token(struct TreeNode *t);
bool node_exists(struct TreeNode *t);
bool has_symbol_table(struct TreeNode *t);
bool is_identifier(struct TreeNode *t);

void print_tree(struct TreeNode *t, int depth = 0);
void print_symbol(struct TreeNode *t);

std::string single_node_string(struct TreeNode *t);

#endif /* _TREENODE_HH_ */