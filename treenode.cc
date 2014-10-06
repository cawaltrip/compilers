#include <string>
#include <iostream>
#include <sstream>
#include "treenode.hh"

/* Stolen and modified from Dr. J's CS-445 HW2 Notes:
 * 	http://www2.cs.uidaho.edu/~jeffery/courses/445/hw2.html
 */
void print_tree(struct TreeNode *t, int depth)
{
	std::stringstream s;
	std::string spaces = std::string(depth*2, ' ');

	s << spaces;
	if(t->num_kids == 0) {
		s << t->t->get_category() << ": " << t->t->get_text();
	} else {
		s << t->prod_text << ": " << t->prod_num;
		s << " (" << t->num_kids << " kids)";
	}
	std::cout << s.str() << std::endl;

	for(int i=0; i<t->num_kids; ++i)
		if(t->kids[i] != NULL)
			print_tree(t->kids[i], depth+1);
}