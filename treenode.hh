#include <string>
#include "token.hh"

struct TreeNode {
	int prod_num;
	std::string prod_text;
	int num_kids;
	struct TreeNode *kids[10];
	Token *t;
};

void print_tree(struct TreeNode *t, int depth = 0);