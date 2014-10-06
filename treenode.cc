#include <string>
#include <iostream>
#include <sstream>
#include "treenode.hh"

extern type_map map;

/* Stolen and modified from Dr. J's CS-445 HW2 Notes:
 * 	http://www2.cs.uidaho.edu/~jeffery/courses/445/hw2.html
 */
void print_tree(struct TreeNode *t, int depth)
{
	std::stringstream s;
	std::string spaces = std::string(depth*2, ' ');

	s << spaces;
	if(t->num_kids == 0) {
		s << "TOKEN (" << t->t->get_category() << "): ";
		s << t->t->get_text();
	} else {
		s << t->prod_text << ": " << t->prod_num;
		s << " (" << t->num_kids << " kids)";
	}
	std::cout << s.str() << std::endl;

	for(int i=0; i<t->num_kids; ++i)
		if(t->kids[i] != NULL)
			print_tree(t->kids[i], depth+1);
}

void add_typename(struct TreeNode *t) {
	/* 
	 * yyerror if already exists (or not a terminal?)
	 * hash code taken from boost tutorial
	 * http://www.boost.org/doc/libs/1_37_0/doc/html/hash/tutorial.html
	 */
	std::pair<std::string,int> typename_pair;
	typename_pair = std::make_pair(t->t->get_text(), t->t->get_category());

	bool found = lookup_typename(t);
	if(!found) {
		std::cout << "`" << t->t->get_text() << "`";
		std::cout << " is being ADDED to the map!" << std::endl;
		map.emplace(typename_pair,t->t->get_text());
	} else {
		std::cerr << t->t->get_text() << " already defined" << std::endl;
		exit(2);
	}
}

bool lookup_typename(struct TreeNode *t) {
	return lookup_typename(t->t->get_text(), t->t->get_category());
}

bool lookup_typename(std::string text, int category) {
	/* return true if found */
	map_iter result;
	std::pair<std::string,int> typename_pair;
	typename_pair = std::make_pair(text, category);

	result = map.find(typename_pair);
	if(result == map.end()) {
		std::cout << "`" << text << "`";
		std::cout << " identifier not in map" << std::endl;
		return false;
	} else {
		std::cout << "`" << text << "`";
		std::cout << " identifier ALREADY IN MAP!" << std::endl;
		return true;
	}	
}