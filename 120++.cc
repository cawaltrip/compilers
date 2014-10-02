#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <unistd.h> /* chdir() */
#include <libgen.h> /* dirname and basename */

#include "lex.yy.h"
#include "token.hh"
#include "120gram.tab.h"

extern int yyparse();
extern int yydebug;

using namespace std;

Token *yytoken;
string yyfilename;

/*
 * First create the lists for storing both the filenames and the tokens.
 * Then, populate the input file list and loop through it, adding the 
 * tokens to a linked list that is printed to the screen.  This is the list 
 * that will become a tree in the next stage.
 */

 /*
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
    	/* TODO: Don't pre-push files to the file stack or else
    	 * only one parse tree will be created.
    	 */
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
	    		/*
	    		int j;
	    		while( (j = yylex()) > 0 ) {
				token_list.push_back(yytoken);
	    		}
	    		*/
	    		yydebug=0;
	    		yyparse();
	    		fclose(fp);
	    		yylineno = 1;
	    		

		} else {
			cout << "Cannot find include file '" << yyfilename;
		}

	}

	/* Print table */
	
	setiosflags(ios::left);

	int catw = 5; /* category width */
	int textw = 25;
	int linew = 5;
	int filew = 20;
	int valw = 25;
	string sep = string(80,'=');

	/*
	cout << left << setw(catw) << "Cat";
	cout << left << setw(textw) << "Text";
	cout << left << setw(linew) << "Line";
	cout << left << setw(filew) << "Filename";
	cout << left << setw(valw) << "Ival/Sval";
	cout << endl;

	cout << sep << endl;

	for (iter = token_list.begin(); iter != token_list.end(); ++iter) {
		stringstream s;
		if ((*iter)->get_category() == INTEGER)
		    s << (*iter)->get_ival();
		else if ((*iter)->get_category() == CHARACTER)
		    s << (*iter)->get_sval();
		else if ((*iter)->get_category() == STRING)
		    s << (*iter)->get_sval();
		else if ((*iter)->get_category() == FLOATING)
			s << (*iter)->get_fval();

		cout << left << setw(catw) << (*iter)->get_category();
		cout << left << setw(textw) << (*iter)->get_text();
		cout << left << setw(linew) << (*iter)->get_lineno();
		cout << left << setw(filew) << (*iter)->get_filename();
		cout << left << setw(valw) << s.str();
		cout << endl;
    	}
    	*/


    return(0);
}