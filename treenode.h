#include "token.hh"

struct TreeNode {
	int production_num;
	int num_kids;
	struct TreeNode *kids[10];
	Token *t;
};