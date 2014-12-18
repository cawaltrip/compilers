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