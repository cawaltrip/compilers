#include <iostream>
#include <fstream>
#include <string>

/*  EasyLogging++ written by Majid Khan.
 *  Version 8.91
 *  Source code available at: https://github.com/easylogging/easyloggingpp
 *  Licensed under MIT License
 */    
#include "easylogging++.h"
#include "lex.yy.h"

using namespace std;

// Enable logging
_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{    
    // Configure Logging
    easyloggingpp::Configurations confFromFile("conf/120++.conf");
    easyloggingpp::Loggers::setDefaultConfigurations(confFromFile,true);
    easyloggingpp::Loggers::reconfigureAllLoggers(confFromFile);

    // Test logging functionality
    LOG(INFO) << "Logging initialized.";

    // Loop through each file that was passed in.
    // Better error handling could be done here!
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