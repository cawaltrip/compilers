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
    //list<token> token_list;
    //list<token>::iterator titer;

    easyloggingpp::Configurations c;
    c.setToDefault();
    c.setAll(easyloggingpp::ConfigurationType::Format, "120++: %level %log");
    easyloggingpp::Loggers::reconfigureAllLoggers(c);
    c.clear();
    c.setAll(easyloggingpp::ConfigurationType::Format, "%log");
    easyloggingpp::Loggers::reconfigureLogger("business", c);
    c.clear();

    LDEBUG << "Logging initialized.";

    for (int i = 1; i < argc; ++i) {
        FILE *fp;
        if ((fp = fopen(argv[i], "r"))!= NULL) {
            file_list.push_back(argv[i]);
            fclose(fp);
        } else {
            LOG(WARNING) << "File '" << argv[i] << "' not found -- not including in compilation";
        }
    }
    for (fiter=file_list.begin(); fiter != file_list.end(); ++fiter) {
        LDEBUG << "Parsing file: " << *fiter;
        yyin = fopen(*fiter, "r");
        int i;
        while( (i = yylex()) > 0 ) {
            BINFO << i << "\t" << yytext;
        }
        fclose(yyin);
    }
    return(0);
}