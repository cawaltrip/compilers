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
#include "token.h"
#include "cgram.tab.h"

struct token *yytoken = NULL;

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
    list<char*> file_list;
    list<char*>::iterator fiter;
    list<struct token*> token_list;
    list<struct token*>::iterator titer;

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
    for (titer = token_list.begin(); titer != token_list.end(); ++titer) {
        std::string value;
        if ((*titer)->category == ICON)
            value = (*titer)->ival;
        else if ((*titer)->category == CCON)
            value = (*titer)->sval;
        else if ((*titer)->category == STRING)
            value = (*titer)->sval;
        //else if ((*titer)->category == FCON)
        //    value = (*titer)->fval;
        else
            value = "";
        BINFO << (*titer)->category << "\t\t" << (*titer)->text << "\t\t" << (*titer)->lineno << "\t\t" << (*titer)->filename << "\t\t" << value;
    }

    return(0);
}