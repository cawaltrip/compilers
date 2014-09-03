#include <iostream>
#include <fstream>
#include <string>


extern FILE *yyin;
extern char *yytext;
extern int yylex(void);

// This allows us to use C++
// even though flex code is compiled
// using gcc and not g++
//extern "C"
//{
//    extern int yylex(void);
//}

using namespace std;

int main(int argc, char *argv[])
{    
    /* Run each input file through flex */
    for (int i = 1; i < argc; ++i)
    {
        yyin = fopen(argv[i],"r");
        if(yyin == NULL)
        {
            fprintf(stderr, "File not found: %s\n", argv[i]);
            return(-1);
        }
        else
        {
            int j = 0;
            while( (j = yylex()) > 0 )
            {
                printf("%d: %s\n",j,yytext);
            }
        }
    }


    return(0);

}