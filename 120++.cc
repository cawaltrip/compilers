#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <unistd.h> /* chdir() */
#include <libgen.h> /* dirname and basename */
#include <boost/program_options.hpp> /* command line arguments parser */

#include "globals.hh"
#include "lex.yy.h"
#include "token.hh"
#include "120gram.tab.h"
#include "treenode.hh"
#include "semantic.hh"

extern int yyparse();
extern int yydebug;
extern TreeNode *root;

using namespace std;
using namespace boost;
namespace po = boost::program_options;

Token *yytoken;
string yyfilename;

/*
 * The main driver of the compiler.  Parses the command line for all 
 * options and files to compile.  Then iterates through each of the
 * input files, creating parse trees and symbols tables for each.  Then
 * the compiler will perform any necessary type checking and will eventually
 * make its way to the intermediate code generation and final code generation
 * stages.
 *
 * TODO:
 *   - Error checking/handling
 */

int main(int argc, char *argv[])
{
	list<Token *> token_list;
	list<Token *>::iterator iter;

	list<string> file_list;
	list<string>::iterator f_iter;

	FILE *fp;

	/* Find valid files from the command line */
	for (int i = 1; i < argc; ++i) {
		string filename = realpath(argv[i], NULL);
		if(filename.empty()) {
			cerr << "Could not expand path " << argv[i];
			exit(EXIT_FAILURE);
		} else if ((fp = fopen(filename.c_str(), "r"))!= NULL) {
			file_list.push_back(filename);
			fclose(fp);
		}
	}

	/* Parse files */
	for (f_iter = file_list.begin(); f_iter != file_list.end(); ++f_iter) {
		char *tmp = strdup(f_iter->c_str());
		char *tmp1 = strdup(tmp);
		yyfilename.assign(basename(tmp));
		chdir(dirname(tmp1));
		free(tmp);
		free(tmp1);

		if ((fp = fopen(yyfilename.c_str(), "r"))!= NULL) {
			yyin = fp;
			yypush_buffer_state(yy_create_buffer(yyin, 
							YY_BUF_SIZE));
			yydebug=0;
			int ret = yyparse();
			fclose(fp);
			yylineno = 1;

			if(!ret) {
				if(PRINT_PARSE_TREES) {
					print_tree(root);
					cout << endl;
				}
			}
		
		} else {
			cout << "Cannot find include file '" << yyfilename;
		}
	}

	return(0);
}