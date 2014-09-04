#include <iostream>
#include <fstream>
#include <string>

#include "easylogging++.h"

extern FILE *yyin;
extern char *yytext;
extern int yylex(void);

using namespace std;

// Enable logging
_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{    
    // Initialize the logging
    easyloggingpp::Configurations confFromFile("conf/120++.cpp.conf");
    easyloggingpp::Loggers::setDefaultConfigurations(confFromFile,true);
    easyloggingpp::Loggers::reconfigureAllLoggers(confFromFile);

    LOG(INFO) << "Logging initialized.";

    for (int i = 1; i < argc; ++i)
    {
        yyin = fopen(argv[i],"r");
        if(yyin == NULL)
        {
            LOG(FATAL) << "File not found: " << argv[i];
            return(-1);
        }
        else
        {
            int j = 0;
            while( (j = yylex()) > 0 )
            {
                cout << j << ": " << yytext << "\n";
            }
        }
    }
    return(0);

}