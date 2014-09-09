%option c++

O        [0-7]
D        [0-9]
L        [a-zA-Z_]
H        [a-fA-F0-9]
E        [Ee][+-]?{D}+
FS       (f|F|l|L)
IS       (u|U|l|L)
W        [ \t\f]*
LIT      \"(\\.|[^\\"])*\"

%{
#include "cgram.tab.h"
#include <string>
#include <fstream>
#include <iostream>
#include "easylogging++.h"

using namespace std;

extern YYSTYPE yylval;
extern int yychar;

void lexerr(char *s);
void handle_user_include_file();

/* #define DEBUG */

int line_num = 1;
int errors;
int included_iostream = 0;
FILE *saved_yyin;
%}

%%

\n                      { line_num++; }
[ \t\f]+                { }

"break"                 { return BREAK; }
"case"                  { return CASE; }
"char"                  { return CHAR; }
"const"                 { return CONST; }
"continue"              { return CONTINUE; }
"default"               { return DEFAULT; }
"do"                    { return DO; }
"double"                { return DOUBLE; }
"else"                  { return ELSE; }
"enum"                  { return ENUM; }
"extern"                { return EXTERN; }
"float"                 { return FLOAT; }
"for"                   { return FOR; }
"goto"                  { return GOTO; }
"if"                    { return IF; }
"int"                   { return INT; }
"long"                  { return LONG; }
"register"              { return REGISTER; }
"return"                { return RETURN; }
"short"                 { return SHORT; }
"signed"                { return SIGNED; }
"sizeof"                { return SIZEOF; }
"static"                { return STATIC; }
"struct"                { return STRUCT; }
"switch"                { return SWITCH; }
"typedef"               { return TYPEDEF; }
"union"                 { return UNION; }
"unsigned"              { return UNSIGNED; }
"void"                  { return VOID; }
"volatile"              { return VOLATILE; }
"while"                 { return WHILE; }

{L}({L}|{D})*           { return IDENTIFIER; }


0[xX]{H}+{IS}?          { lexerr("Hex not supported\n"); }

0{O}+{IS}?              { lexerr("Octal not supported\n"); }

{D}+{IS}?               {
			  return ICON; }

'(\\.|[^\\'])+'         {
			  return CCON;
			}

{D}+{E}{FS}?            {
			  return FCON; }
{D}*"."{D}+({E})?{FS}?  {
			  return FCON; }
{D}+"."{D}*({E})?{FS}?  {
			  return FCON; }

{LIT}                   {
			  return STRING; }

"#include"[ ]*\"[^\\"]+\"  { handle_user_include_file(); }

"#include <iostream>"   { included_iostream = 1; }

">>="                   { return SRASN; }
"<<="                   { return SLASN; }
"+="                    { return PLASN; }
"-="                    { return MIASN; }
"*="                    { return MUASN; }
"/="                    { return DIASN; }
"%="                    { return MOASN; }
"&="                    { return ANASN; }
"^="                    { return ERASN; }
"|="                    { return ORASN; }
">>"                    { return SHR; }
"<<"                    { return SHL; }
"++"                    { return INCOP; }
"--"                    { return DECOP; }
"->"                    { return FOLLOW; }
"&&"                    { return ANDAND; }
"||"                    { return OROR; }
"<="                    { return LE; }
">="                    { return GE; }
"=="                    { return EQ; }
"!="                    { return NE; }
";"                     { return SM; }
"{"                     { return LC; }
"}"                     { return RC; }
","                     { return CM; }
":"                     { return COLON; }
"="                     { return ASN; }
"("                     { return LP; }
")"                     { return RP; }
"["                     { return LB; }
"]"                     { return RB; }
"."                     { return DOT; }
"&"                     { return AND; }
"!"                     { return BANG; }
"~"                     { return NOT; }
"-"                     { return MINUS; }
"+"                     { return PLUS; }
"*"                     { return MUL; }
"/"                     { return DIV; }
"%"                     { return MOD; }
"<"                     { return LT; }
">"                     { return GT; }
"^"                     { return ER; }
"|"                     { return OR; }
"?"                     { return QUEST; }
<<EOF>>                 {
                            yypop_buffer_state();
                            if(!YY_CURRENT_BUFFER)
                                yyterminate();
                        }
%%


void lexerr(char *s)
{
	errors++;

	fprintf(stderr, "%s: lexical error", s);

	/* to do: add mechanism for reporting file name and line number */

	fprintf(stderr, ", token = \"%s\"\n", yytext);
}

/*
 * Return 1 if done, 0 if yyin points at more input
 */
int yywrap()
{
    return 1;
}

void handle_user_include_file()
{
    /* 
    * Create a new string that contains only the file name
    * to be included.
    */
    string newfile;
    int startIndex = strchr(yytext, '\"')+1 - yytext;
    int endIndex = strlen(yytext)-1;
    int stringLength = endIndex - startIndex;

    newfile.assign(yytext,startIndex,stringLength);

    //saved_yyin = yyin;
    yyin = fopen(newfile.c_str(),"r");
    if (!yyin) 
    {
        //lexerr("cannot open include file");
        LOG(ERROR) << "Cannot open include file";
        exit(1);
    }
    else
    {
        yypush_buffer_state(yy_new_buffer(yyin, YY_BUF_SIZE));
    }

}
