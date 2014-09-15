%option header-file="lex.yy.h"
%option noyywrap
%option yylineno
%x COMMENT STR

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
#include <string>
#include <fstream>
#include <iostream>
#include "cgram.tab.h"
#include "token.hh"
#include "easylogging++.h"

extern YYSTYPE yylval;
extern int yychar;
extern struct token *yytoken;

void lexerr(char *s);
void handle_user_include_file();
void create_token(int category);
void start_string_match();
void append_string_match(const char *text);
void append_string_match(const char *sval, const char *text);

int errors;

int sysinclude_iostream = 0;
int sysinclude_string = 0;
int sysinclude_iomanip = 0;
int sysinclude_fstream = 0;
int sysinclude_cstring = 0;
int sysinclude_ctime = 0;
int sysinclude_cmath = 0;
int sysinclude_cstdlib = 0;

/* strings for string matching */
std::string token_sval;
std::string token_text;
%}

%%

  /* Whitespace */
[ \n\r\v\t\f]*		{ }

  /* Comments */
"//".*$                 { }
"/*"                    { BEGIN(COMMENT); }
<COMMENT>{
	[^*]*           { }
	"*"+[^*/]*      { }
	"*"+"/"         { BEGIN(INITIAL); }
}

  /* String Constants -- adapted from http://stackoverflow.com/a/5423131 */
\"			{ start_string_match(); }
<STR>{
	[^\\"\n]*	{ append_string_match(yytext); }
	\\n		{ append_string_match(yytext, '\n'); }
	\\t		{ append_string_match(yytext, '\t'); }
	\\[\\"]		{ append_string_match(yytext, '\"'); }
	\"		{ end_string_match(STRING); 
			  BEGIN(INITIAL); return STRING; }
	\\.		{ LOG(ERROR) << "Invalid escape sequence"; }
	\n		{ LOG(ERROR) << "Newline in string literal"; }
}

  /* Character Constants */
'(\\.|[^\\'])+'         { create_token(CCON); return CCON; }

  /* Integer Constants */
{D}+{IS}?               { create_token(ICON); return ICON; }

  /* Floating-point Constants */
{D}+{E}{FS}?            { create_token(FCON); return FCON; }
{D}*"."{D}+({E})?{FS}?  { create_token(FCON); return FCON; }
{D}+"."{D}*({E})?{FS}?  { create_token(FCON); return FCON; }

  /* Reserved Words */
"break"                 { create_token(BREAK);      return BREAK; }
"case"                  { create_token(CASE);       return CASE; }
"char"                  { create_token(CHAR);       return CHAR; }
"const"                 { create_token(CONST);      return CONST; }
"continue"              { create_token(CONTINUE);   return CONTINUE; }
"default"               { create_token(DEFAULT);    return DEFAULT; }
"do"                    { create_token(DO);         return DO; }
"double"                { create_token(DOUBLE);     return DOUBLE; }
"else"                  { create_token(ELSE);       return ELSE; }
"enum"                  { create_token(ENUM);       return ENUM; }
"extern"                { create_token(EXTERN);     return EXTERN; }
"float"                 { create_token(FLOAT);      return FLOAT; }
"for"                   { create_token(FOR);        return FOR; }
"goto"                  { create_token(GOTO);       return GOTO; }
"if"                    { create_token(IF);         return IF; }
"int"                   { create_token(INT);        return INT; }
"long"                  { create_token(LONG);       return LONG; }
"register"              { create_token(REGISTER);   return REGISTER; }
"return"                { create_token(RETURN);     return RETURN; }
"short"                 { create_token(SHORT);      return SHORT; }
"signed"                { create_token(SIGNED);     return SIGNED; }
"sizeof"                { create_token(SIZEOF);     return SIZEOF; }
"static"                { create_token(STATIC);     return STATIC; }
"struct"                { create_token(STRUCT);     return STRUCT; }
"switch"                { create_token(SWITCH);     return SWITCH; }
"typedef"               { create_token(TYPEDEF);    return TYPEDEF; }
"union"                 { create_token(UNION);      return UNION; }
"unsigned"              { create_token(UNSIGNED);   return UNSIGNED; }
"void"                  { create_token(VOID);       return VOID; }
"volatile"              { create_token(VOLATILE);   return VOLATILE; }
"while"                 { create_token(WHILE);      return WHILE; }

  /* Identifiers */
{L}({L}|{D})*           { create_token(IDENTIFIER); return IDENTIFIER; }

0[xX]{H}+{IS}?          { lexerr("Hex not supported\n"); }

0{O}+{IS}?              { lexerr("Octal not supported\n"); }


"#include"[ ]*\"[^\\"]+\"  { handle_user_include_file(); }

"#include <iostream>"   { sysinclude_iostream = 1; }
"#include <string>"     { sysinclude_string = 1; }
"#include <iomanip>"    { sysinclude_iomanip = 1; }
"#include <fstream>"    { sysinclude_fstream = 1; }
"#include <cstring>"    { sysinclude_cstring = 1; }
"#include <ctime>"      { sysinclude_ctime = 1; }
"#include <cmath>"      { sysinclude_cmath = 1; }
"#include <cstdlib>"    { sysinclude_cstdlib = 1; }
"#include"{W}"<"[A-Za-z.]*">"       {  }

">>="                   {create_token(SRASN); return SRASN; } 
"<<="                   {create_token(SLASN); return SLASN; } 
"+="                    {create_token(PLASN); return PLASN; } 
"-="                    {create_token(MIASN); return MIASN; } 
"*="                    {create_token(MUASN); return MUASN; } 
"/="                    {create_token(DIASN); return DIASN; } 
"%="                    {create_token(MOASN); return MOASN; } 
"&="                    {create_token(ANASN); return ANASN; } 
"^="                    {create_token(ERASN); return ERASN; } 
"|="                    {create_token(ORASN); return ORASN; } 
">>"                    {create_token(SHR); return SHR; } 
"<<"                    {create_token(SHL); return SHL; } 
"++"                    {create_token(INCOP); return INCOP; } 
"--"                    {create_token(DECOP); return DECOP; } 
"->"                    {create_token(FOLLOW); return FOLLOW; } 
"&&"                    {create_token(ANDAND); return ANDAND; } 
"||"                    {create_token(OROR); return OROR; } 
"<="                    {create_token(LE); return LE; } 
">="                    {create_token(GE); return GE; } 
"=="                    {create_token(EQ); return EQ; } 
"!="                    {create_token(NE); return NE; } 
";"                     {create_token(SM); return SM; } 
"{"                     {create_token(LC); return LC; } 
"}"                     {create_token(RC); return RC; } 
","                     {create_token(CM); return CM; } 
":"                     {create_token(COLON); return COLON; } 
"="                     {create_token(ASN); return ASN; } 
"("                     {create_token(LP); return LP; } 
")"                     {create_token(RP); return RP; } 
"["                     {create_token(LB); return LB; } 
"]"                     {create_token(RB); return RB; } 
"."                     {create_token(DOT); return DOT; } 
"&"                     {create_token(AND); return AND; } 
"!"                     {create_token(BANG); return BANG; } 
"~"                     {create_token(NOT); return NOT; } 
"-"                     {create_token(MINUS); return MINUS; } 
"+"                     {create_token(PLUS); return PLUS; } 
"*"                     {create_token(MUL); return MUL; } 
"/"                     {create_token(DIV); return DIV; } 
"%"                     {create_token(MOD); return MOD; } 
"<"                     {create_token(LT); return LT; } 
">"                     {create_token(GT); return GT; } 
"^"                     {create_token(ER); return ER; } 
"|"                     {create_token(OR); return OR; } 
"?"                     {create_token(QUEST); return QUEST; } 
<<EOF>>                 {
			    yypop_buffer_state();
			    yylineno = 1;
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

void handle_user_include_file()
{
    /* 
    * Create a new string that contains only the file name
    * to be included.
    */
    std::string newfile;
    int startIndex = strchr(yytext, '\"')+1 - yytext;
    int endIndex = strlen(yytext)-1;
    int stringLength = endIndex - startIndex;

    newfile.assign(yytext,startIndex,stringLength);

    yyin = fopen(newfile.c_str(),"r");
    if (!yyin) 
    {
	LOG(ERROR) << "Cannot open include file";
	exit(1);
    }
    else
    {
	yypush_buffer_state(yy_new_buffer(yyin, YY_BUF_SIZE));
    }

}
void create_token(int category) {
	yytoken = new Token(category, yylineno, "unknown", yytext);
}
void start_string_match() {
	token_sval.clear();
	token_text.clear();
	token_sval = "\"";
}

void append_string_match(const char *text) {
	append_string_match(text, text);
}

void append_string_match(const char *sval, const char *text) {
	token_sval.append(sval);
	token_text.append(text);	
}

void end_string_match(int category) {
	token_sval.append("\"");
	yytoken = new Token(category, yylineno, "unknown",
				token_text, token_sval);
}