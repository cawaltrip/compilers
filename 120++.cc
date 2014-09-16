#include <iostream>
#include <fstream>
#include <string>
#include <list>

/*  EasyLogging++ written by Majid Khan.
 *  Version 8.91
 *  Source code available at: https://github.com/easylogging/easyloggingpp
 *  Licensed under MIT License
 */    
#include "easylogging++.h"
#include "lex.yy.h"
#include "token.hh"
#include "cgram.tab.h"

Token *yytoken;
//struct token *yytoken = NULL;

using namespace std;

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

    easyloggingpp::Configurations c;
    c.setToDefault();
    c.setAll(easyloggingpp::ConfigurationType::Format, "120++: %level %log");
    easyloggingpp::Loggers::reconfigureAllLoggers(c);
    c.clear();
    c.setAll(easyloggingpp::ConfigurationType::Format, "%log");
    easyloggingpp::Loggers::reconfigureLogger("business", c);
    c.clear();

    for (int i = 1; i < argc; ++i) {
        FILE *fp;
        if ((fp = fopen(argv[i], "r"))!= NULL) {
            yyin = fp;
            yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
            
            int i;
            while( (i = yylex()) > 0 ) {
                token_list.push_back(yytoken);
            }
            fclose(fp);
            yylineno = 1;
        } else {
            LOG(WARNING) << "File '" << argv[i] << "' not found -- not including in compilation";
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