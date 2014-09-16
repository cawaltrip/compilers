%option header-file="lex.yy.h"
%option noyywrap
%option yylineno
%x COMMENT STR INCLUDE CHR CHR_END

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
extern Token *yytoken;
extern std::string current_filename;

void lexerr(std::string s);

void handle_user_include_file();

void create_token(int category);

void start_string_match();
void append_string_match(const char *text);
void append_string_match(const char *text, const char *sval);
void append_string_match(char escape, const char *sval);
void append_string_match(const char *text, char escape);
void append_string_match(char text_escape, char sval_escape);
void end_string_match(int category);

void start_character_match();
void set_character_match(const char* text, char match);
void end_character_match(int category);

int errors = 0;

/* include file flags */
int sysinclude_cmath = 0;
int sysinclude_cstdlib = 0;
int sysinclude_cstring = 0;
int sysinclude_ctime = 0;
int sysinclude_fstream = 0;
int sysinclude_iomanip = 0;
int sysinclude_iostream = 0;
int sysinclude_string = 0;

/* strings for string matching */
std::string token_val;
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

  /* String Constants 
   *	Adapted from: http://stackoverflow.com/a/5423131 
   *	Escape character sequence from: 
   * 		http://en.wikipedia.org/wiki/String_literal#Escape_sequences	
   */
  
\"			{ start_string_match(); BEGIN(STR); }
<STR>{
	[^\\"\n]*	{ append_string_match(yytext); }
	\\0		{ append_string_match(yytext, '\0'); }
	\\a		{ append_string_match(yytext, '\a'); }
	\\b		{ append_string_match(yytext, '\b'); }
	\\f		{ append_string_match(yytext, '\f'); }
	\\n		{ append_string_match(yytext, '\n'); }
	\\r		{ append_string_match(yytext, '\r'); }
	\\t		{ append_string_match(yytext, '\t'); }
	\\v		{ append_string_match(yytext, '\v'); }
	\\[\\"]		{ append_string_match(yytext, '\"'); }
	\\\		{ append_string_match(yytext, '\\'); }
	\\'		{ append_string_match(yytext, '\''); }
	\"		{ end_string_match(STRING); 
			  BEGIN(INITIAL); return STRING; }
	\\u{H}{4}	{ lexerr("16-bit unicode not supported"); }
	\\U{H}{6}	{ lexerr("32-bit unicode not supported"); }
	\\x{H}{2}	{ lexerr("Hexadecimal ASCII not supported"); }
	\\{O}{4}	{ lexerr("Octal ASCII not supported"); }
	\\.		{ lexerr("Invalid escape sequence"); }
	\n		{ lexerr("Newline in string literal"); }
	<<EOF>>		{ lexerr("EOF reached before closing \" found"); }
}

  /* Character Constants */
\'			{ start_character_match(); BEGIN(CHR); }
<CHR>{
	\\0		{ set_character_match(yytext, '\0'); BEGIN(CHR_END); }
	\\a		{ set_character_match(yytext, '\a'); BEGIN(CHR_END); }
	\\b		{ set_character_match(yytext, '\b'); BEGIN(CHR_END); }
	\\f		{ set_character_match(yytext, '\f'); BEGIN(CHR_END); }
	\\n		{ set_character_match(yytext, '\n'); BEGIN(CHR_END); }
	\\r		{ set_character_match(yytext, '\r'); BEGIN(CHR_END); }
	\\t		{ set_character_match(yytext, '\t'); BEGIN(CHR_END); }
	\\v		{ set_character_match(yytext, '\v'); BEGIN(CHR_END); }
	\\[\\"]		{ set_character_match(yytext, '\"'); BEGIN(CHR_END); }
	\\\		{ set_character_match(yytext, '\\'); BEGIN(CHR_END); }
	\\'		{ set_character_match(yytext, '\''); BEGIN(CHR_END); }
	.		{ set_character_match(yytext, yytext[0]); 
			  BEGIN(CHR_END); }
	<<EOF>>		{ lexerr("EOF reached while matching character"); }
}
<CHR_END>{
	\'		{ end_character_match(CCON);
			  BEGIN(INITIAL); return CCON; }
	<<EOF>>		{ lexerr("EOF reached while closing character"); }
	.		{ lexerr("Character constants must be 1 character"); }
}

  /* Integer Constants */
0[xX]{H}+{IS}?          { lexerr("Hexadecimal not supported"); }
0{O}+{IS}?              { lexerr("Octal not supported"); }
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

  /* Include Files */
"#include"		{ BEGIN(INCLUDE); }
<INCLUDE>{
	[ \t]*		{ /* eat whitespace on both sides of include */ }
	"<cmath>"	{ sysinclude_cmath       = 1; BEGIN(INITIAL); }
	"<cstdlib>"	{ sysinclude_cstdlib     = 1; BEGIN(INITIAL); }
	"<cstring>"	{ sysinclude_cstring     = 1; BEGIN(INITIAL); }
	"<ctime>"	{ sysinclude_ctime       = 1; BEGIN(INITIAL); }
	"<fstream>"	{ sysinclude_fstream     = 1; BEGIN(INITIAL); }
	"<iomanip>"	{ sysinclude_iomanip     = 1; BEGIN(INITIAL); }
	"<iostream>"	{ sysinclude_iostream    = 1; BEGIN(INITIAL); }
	"<string>"	{ sysinclude_string      = 1; BEGIN(INITIAL); }
	\"[^\\"]+\"	{ handle_user_include_file(); BEGIN(INITIAL); }
	"<"[^<>]*">"	{ lexerr("Unknown system include file"); }
	<<EOF>>		{ lexerr("EOF reached unexpectedly from include"); }
}

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


void lexerr(std::string s)
{
	errors++;
	LOG(ERROR) << current_filename << ": lexical error on line " << yylineno << ": " << s;
	LOG(ERROR) << current_filename << ": \t\tcurrent token: " << yytext;
	exit(EXIT_FAILURE);

	/* to do: add mechanism for reporting file name and line number */
	//fprintf(stderr, ", token = \"%s\"\n", yytext);
}

void handle_user_include_file()
{
    /* 
    * Create a new string that contains only the file name
    * to be included.
    */
	std::string include = yytext;
	std::string filename = include.substr(1, (strlen(yytext)-2));

	yyin = fopen(filename.c_str(),"r");
	if (!yyin) {
		lexerr("Cannot open include file '" + filename + "'");
		exit(EXIT_FAILURE);
	}
	else
		yypush_buffer_state(yy_new_buffer(yyin, YY_BUF_SIZE));
}

void create_token(int category) {
	yytoken = new Token(category, yylineno, current_filename, yytext);
}
void start_string_match() {
	token_text.clear();
	token_val.clear();
	token_text = "\"";
}

void append_string_match(const char *text) {
	append_string_match(text, text);
}

void append_string_match(const char *text, const char *sval) {
	token_text.append(text);
	token_val.append(sval);
}

void append_string_match(char escape, const char *sval) {
	token_text.append(1, escape);
	token_val.append(sval);
}

void append_string_match(const char *text, char escape) {
	token_text.append(text);
	token_val.append(1, escape);
}

void append_string_match(char text_escape, char sval_escape) {
	token_text.append(1, text_escape);
	token_val.append(1, sval_escape);
}

void end_string_match(int category) {
	token_text.append(1, '"');
	yytoken = new Token(category, yylineno, current_filename,
					token_text, token_val);
}

void start_character_match() {
	token_text.clear();
	token_val.clear();
	token_text = "\'";
}

void set_character_match(const char* text, char match) {
	token_text += text;
	token_val = match;
}
void end_character_match(int category) {
	token_text += "'";
	yytoken = new Token(category, yylineno, current_filename, 
						token_text, token_val);
}