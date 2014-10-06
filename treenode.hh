#ifndef _TREENODE_HH_
#define _TREENODE_HH_

#include <string>
#include <boost/functional/hash/hash.hpp>
#include <boost/unordered_map.hpp>
#include "token.hh"


/* Typename lookup table */
typedef boost::unordered_map<std::pair<std::string,int>,std::string> type_map;
typedef type_map::const_iterator map_iter;

struct TreeNode {
	int prod_num;
	std::string prod_text;
	int num_kids;
	struct TreeNode *kids[10];
	Token *t;
};

void print_tree(struct TreeNode *t, int depth = 0);
void add_typename(struct TreeNode *t);
bool lookup_typename(struct TreeNode *t);
bool lookup_typename(std::string, int);

#endif /* _TREENODE_HH_ */