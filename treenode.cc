#include <string>
#include <iostream>
#include "treenode.hh"

/* Stolen and modified from Dr. J's CS-445 HW2 Notes:
 * 	http://www2.cs.uidaho.edu/~jeffery/courses/445/hw2.html
 */
void print_tree(struct TreeNode *t, int depth)
{
	std::string spaces = std::string(depth*2, ' ');
	std::cout << spaces << t->prod_text << ": " << t->prod_num 
		<< " (" << t->num_kids << " kids)" << std::endl;

	for(int i=0; i<t->num_kids; ++i)
		print_tree(t->kids[i], depth+1);
}