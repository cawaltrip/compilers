#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unistd.h> /* chdir() */
#include <libgen.h> /* dirname and basename */
/*  EasyLogging++ written by Majid Khan.
 *  Version 8.91
 *  Source code available at: https://github.com/easylogging/easyloggingpp
 *  Licensed under MIT License
 */    
#include "easylogging++.h"
#include "lex.yy.h"
#include "token.hh"
#include "cgram.tab.h"

using namespace std;

Token *yytoken;
string current_filename;

/* Enable logging */
_INITIALIZE_EASYLOGGINGPP

/*
 * First create the lists for storing both the filenames and the tokens.
 * Then, configure (and test?) the logging features.  Finally, populate the
 * input file list and loop through it, adding the tokens to a linked
 * list that is printed to the screen.  This is the list that will become a
 * tree in the next stage.
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

	easyloggingpp::Configurations c;
	c.setToDefault();
	c.setAll(easyloggingpp::ConfigurationType::Format, 
					"120++: %level %log");
	easyloggingpp::Loggers::reconfigureAllLoggers(c);
	c.clear();
	c.setAll(easyloggingpp::ConfigurationType::Format, "%log");
	easyloggingpp::Loggers::reconfigureLogger("business", c);
	c.clear();

    	FILE *fp;

    	/* Find valid files from the command line */
	for (int i = 1; i < argc; ++i) {
		string filename = realpath(argv[i], NULL);
		if(filename.empty()) {
			LOG(ERROR) << "Could not expand path " << argv[i];
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
		current_filename.assign(basename(tmp));
		chdir(dirname(tmp1));
		free(tmp);
		free(tmp1);

		if ((fp = fopen(current_filename.c_str(), "r"))!= NULL) {
			yyin = fp;
	    		yypush_buffer_state(yy_create_buffer(yyin, 
	    						YY_BUF_SIZE));
	    		int j;
	    		while( (j = yylex()) > 0 ) {
				token_list.push_back(yytoken);
	    		}
	    		fclose(fp);
	    		yylineno = 1;
		} else {
			LOG(WARNING) << "Cannot find include file '" << current_filename;
		}

	}

    BINFO << "Category \t\t Text \t\t Line \t\t Filename \t\t Ival/Sval";
    BINFO << "=================================================================";
    for (iter = token_list.begin(); iter != token_list.end(); ++iter) {
	std::string value;
	if ((*iter)->get_category() == ICON)
	    value = (*iter)->get_ival();
	else if ((*iter)->get_category() == CCON)
	    value = (*iter)->get_sval();
	else if ((*iter)->get_category() == STRING)
	    value = (*iter)->get_sval();
	//else if ((*iter)->get_category() == FCON)
	//    value = (*iter)->get_fval();
	else
	    value = "";
	BINFO << (*iter)->get_category() << "\t\t" << (*iter)->get_text() << "\t\t" << (*iter)->get_lineno() << "\t\t" << (*iter)->get_filename() << "\t\t" << value;
    }

    return(0);
}