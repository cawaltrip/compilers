%option header-file="lex.yy.h"
%option noyywrap
%option yylineno
%x COMMENT STR INCLUDE CHR CHR_END

  /* Bases */
O        [0-7]
D        [0-9]
L        [a-zA-Z_]
H        [a-fA-F0-9]

  /* Integers */
IS       (u|U|l|L)

  /* Floating-points */
FP	({D}*\.{D}+)|({D}+\.)
E        [Ee][+-]?{D}+
FS       (f|F|l|L)

  /* Spaces */
W        [ \t\f]*

  /* Literals */
LIT      \"(\\.|[^\\"])*\"

%{
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <libgen.h> /* dirname and basename */
#include "120gram.tab.h"
#include "token.hh"
#include "treenode.hh"
#include "hashmap.hh"

extern LookupTable ident_table;
extern int yychar;
extern Token *yytoken;
extern std::string yyfilename;

void lexerr(std::string s);

void add_to_lookup(std::deque<std::string> filelist, int category);
std::deque<std::string> get_sysinclude_fstream();
std::deque<std::string> get_sysinclude_iostream();
std::deque<std::string> get_sysinclude_string();

void handle_user_include_file();
int check_identifier(std::string str);

void create_token(int cat, int line, std::string file, 
			std::string text, std::string val = "");
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

std::string get_current_filename();
void push_include_file(std::string inc);
void pop_include_file();

int errors = 0;

/* system include faking */
int sysinclude_cmath = 0;
int sysinclude_cstdlib = 0;
int sysinclude_cstring = 0;
int sysinclude_ctime = 0;
int sysinclude_fstream = 0;
int sysinclude_iomanip = 0;
int sysinclude_iostream = 0;
int sysinclude_string = 0;

/* namespace faking */
int namespace_std = 0;

/* literal construction */
std::string token_val;
std::string token_text;

/* is this an included file */
std::list<std::string> include_stack;

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

  /* Standard Library Faking */
  /* Match ; as well otherwise empty statement and syntax error */
"using"{W}"namespace"{W}"std"{W}";"	{ namespace_std = 1; /* No token */ }

  /* Reserved Words */
"asm"			{ create_token(ASM);		return ASM; }
"auto"			{ create_token(AUTO);		return AUTO; }
"bool"			{ create_token(BOOL);		return BOOL; }
"break"                 { create_token(BREAK);      return BREAK; }
"case"                  { create_token(CASE);       return CASE; }
"catch"			{ create_token(CATCH);		return CATCH; }
"char"                  { create_token(CHAR);       return CHAR; }
"class"			{ create_token(CLASS); 		return CLASS; }
"const"                 { create_token(CONST);      return CONST; }
"const_class"		{ create_token(CONST_CAST);	return CONST_CAST; }
"continue"              { create_token(CONTINUE);   return CONTINUE; }
"default"               { create_token(DEFAULT);    return DEFAULT; }
"delete"		{ create_token(DELETE);		return DELETE; }
"do"                    { create_token(DO);         return DO; }
"double"                { create_token(DOUBLE);     return DOUBLE; }
"dynamic_cast"		{ create_token(DYNAMIC_CAST);	return DYNAMIC_CAST; }
"else"                  { create_token(ELSE);       return ELSE; }
"enum"                  { create_token(ENUM);       return ENUM; }
"explicit"		{ create_token(EXPLICIT);	return EXPLICIT; }
"export"		{ create_token(EXPORT);		return EXPORT; }
"extern"                { create_token(EXTERN);     return EXTERN; }
"false"			{ create_token(FALSE); 		return FALSE; }
"float"                 { create_token(FLOAT);      return FLOAT; }
"for"                   { create_token(FOR);        return FOR; }
"friend"		{ create_token(FRIEND);		return FRIEND; }
"goto"                  { create_token(GOTO);       return GOTO; }
"if"                    { create_token(IF);         return IF; }
"inline"		{ create_token(INLINE);		return INLINE; }
"int"                   { create_token(INT);        return INT; }
"long"                  { create_token(LONG);       return LONG; }
"mutable"		{ create_token(MUTABLE);	return MUTABLE; }
"namespace"		{ create_token(NAMESPACE);	return NAMESPACE; }
"new"			{ create_token(NEW);		return NEW; }
"operator"		{ create_token(OPERATOR);	return OPERATOR; }
"private"		{ create_token(PRIVATE);	return PRIVATE; }
"protected"		{ create_token(PROTECTED);	return PROTECTED; }
"public"		{ create_token(PUBLIC);		return PUBLIC; }
"register"              { create_token(REGISTER);   return REGISTER; }
"reinterpret_cast"	{ create_token(REINTERPRET_CAST); 
			  return REINTERPRET_CAST; }
"return"                { create_token(RETURN);     return RETURN; }
"short"                 { create_token(SHORT);      return SHORT; }
"signed"                { create_token(SIGNED);     return SIGNED; }
"sizeof"                { create_token(SIZEOF);     return SIZEOF; }
"static"                { create_token(STATIC);     return STATIC; }
"static_cast"		{ create_token(STATIC_CAST);	return STATIC_CAST; }
"struct"                { create_token(STRUCT);     return STRUCT; }
"switch"                { create_token(SWITCH);     return SWITCH; }
"template"		{ create_token(TEMPLATE);	return TEMPLATE; }
"this"			{ create_token(THIS); 		return THIS; }
"throw"			{ create_token(THROW); 		return THROW; }
"true"			{ create_token(TRUE);		return TRUE; }
"try"			{ create_token(TRY); 		return TRY; }
"typedef"               { create_token(TYPEDEF);    return TYPEDEF; }
"typeid"		{ create_token(TYPEID);		return TYPEID; }
"typename"		{ create_token(TYPENAME);	return TYPENAME; }
"union"                 { create_token(UNION);      return UNION; }
"unsigned"              { create_token(UNSIGNED);   return UNSIGNED; }
"using"			{ create_token(USING);		return USING; }
"virtual"		{ create_token(VIRTUAL);	return VIRTUAL; }
"void"                  { create_token(VOID);       return VOID; }
"volatile"              { create_token(VOLATILE);   return VOLATILE; }
"wchar_t"		{ create_token(WCHAR_T);	return WCHAR_T; }
"while"                 { create_token(WHILE);      return WHILE; }

  /* Include Files */
"#include"		{ BEGIN(INCLUDE); }
<INCLUDE>{
	[ \t]*		{ /* eat whitespace on both sides of include */ }
	"<cmath>"	{ sysinclude_cmath       = 1; BEGIN(INITIAL); }
	"<cstdlib>"	{ sysinclude_cstdlib     = 1; BEGIN(INITIAL); }
	"<cstring>"	{ sysinclude_cstring     = 1; BEGIN(INITIAL); }
	"<ctime>"	{ sysinclude_ctime       = 1; BEGIN(INITIAL); }
	"<fstream>"	{ sysinclude_fstream     = 1;
			  add_to_lookup(get_sysinclude_fstream(), CLASS_NAME);
			  BEGIN(INITIAL); }
	"<iomanip>"	{ sysinclude_iomanip     = 1; BEGIN(INITIAL); }
	"<iostream>"	{ sysinclude_iostream    = 1; 
			  add_to_lookup(get_sysinclude_iostream(), IDENTIFIER);
			  BEGIN(INITIAL); }
	"<string>"	{ sysinclude_string      = 1; 
			  add_to_lookup(get_sysinclude_string(), CLASS_NAME);
			  BEGIN(INITIAL); }
	\"[^\\"]+\"	{ handle_user_include_file(); BEGIN(INITIAL); }
	"<"[^<>]*">"	{ lexerr("Unknown system include file"); }
	<<EOF>>		{ lexerr("EOF reached unexpectedly from include"); }
}

">>="                   { create_token(SREQ); return SREQ; } 
"<<="                   { create_token(SLEQ); return SLEQ; } 
"+="                    { create_token(ADDEQ); return ADDEQ; } 
"-="                    { create_token(SUBEQ); return SUBEQ; } 
"*="                    { create_token(MULEQ); return MULEQ; } 
"/="                    { create_token(DIVEQ); return DIVEQ; } 
"%="                    { create_token(MODEQ); return MODEQ; } 
"&="                    { create_token(ANDEQ); return ANDEQ; }
"and_eq"		{ create_token(ANDEQ); return ANDEQ; } 
"^="                    { create_token(XOREQ); return XOREQ; }
"xor_eq"		{ create_token(XOREQ); return XOREQ; } 
"|="                    { create_token(OREQ); return OREQ; }
"or_eq"			{ create_token(OREQ); return OREQ; }
">>"                    { create_token(SR); return SR; } 
"<<"                    { create_token(SL); return SL; } 
"++"                    { create_token(PLUSPLUS); return PLUSPLUS; } 
"--"                    { create_token(MINUSMINUS); return MINUSMINUS; } 
"->"                    { create_token(ARROW); return ARROW; } 
"->*"			{ create_token(ARROWSTAR); return ARROWSTAR; }
"&&"                    { create_token(ANDAND); return ANDAND; } 
"and"			{ create_token(ANDAND); return ANDAND; }
"||"                    { create_token(OROR); return OROR; } 
"or"			{ create_token(OROR); return OROR; }
"<="                    { create_token(LTEQ); return LTEQ; } 
">="                    { create_token(GTEQ); return GTEQ; } 
"=="                    { create_token(EQ); return EQ; } 
"!="                    { create_token(NOTEQ); return NOTEQ; }
"not_eq"		{ create_token(NOTEQ); return NOTEQ; }

";"                     { create_token(';'); return ';'; } 
"{"                     { create_token('{'); return '{'; }
"<%"			{ create_token('{'); return '{'; } 
"}"                     { create_token('}'); return '}'; }
"%>"			{ create_token('}'); return '}'; } 
","                     { create_token(','); return ','; } 
":"                     { create_token(':'); return ':'; }
"::"			{ create_token(COLONCOLON); return COLONCOLON; } 
"="                     { create_token('='); return '='; } 
"("                     { create_token('('); return '('; } 
")"                     { create_token(')'); return ')'; } 
"["                     { create_token('['); return '['; } 
"<:"			{ create_token('['); return '['; }
"]"                     { create_token(']'); return ']'; }
":>"			{ create_token(']'); return ']'; } 
"."                     { create_token('.'); return '.'; }
"..."			{ create_token(ELLIPSIS); return ELLIPSIS; }
".*"			{ create_token(DOTSTAR); return DOTSTAR; } 
"&"                     { create_token('&'); return '&'; } 
"bitand"		{ create_token('&'); return '&'; }
"!"                     { create_token('!'); return '!'; }
"not"			{ create_token('!'); return '!'; } 
"~"                     { create_token('~'); return '~'; } 
"compl"			{ create_token('~'); return '~'; }
"-"                     { create_token('-'); return '-'; } 
"+"                     { create_token('+'); return '+'; } 
"*"                     { create_token('*'); return '*'; } 
"/"                     { create_token('/'); return '/'; } 
"%"                     { create_token('%'); return '%'; } 
"<"                     { create_token('<'); return '<'; } 
">"                     { create_token('>'); return '>'; } 
"^"                     { create_token('^'); return '^'; } 
"xor"			{ create_token('^'); return '^'; }
"|"                     { create_token('|'); return '|'; }
"bitor"			{ create_token('|'); return '|'; } 
"?"                     { create_token('?'); return '?'; } 

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
	\'		{ end_character_match(CHARACTER);
			  BEGIN(INITIAL); return CHARACTER; }
	<<EOF>>		{ lexerr("EOF reached while closing character"); }
	.		{ lexerr("Character constants must be 1 character"); }
}

  /* Integer Constants */
{D}+{IS}?               { create_token(INTEGER); return INTEGER; }


  /* Floating-point Constants */
{FP}{E}?{FS}?		{ create_token(FLOATING);	return FLOATING; }
{D}+{E}{FS}?		{ create_token(FLOATING);	return FLOATING; }

  /* Identifiers */
{L}({L}|{D})*           { return check_identifier(yytext); }

  /* End of File */
<<EOF>>                 {
				pop_include_file();
				yypop_buffer_state();
				yylineno = 1;
				if(!YY_CURRENT_BUFFER)
					yyterminate();
			}
%%

void lexerr(std::string str)
{
	/* TODO: Add a list of errors */
	std::stringstream s;
	s << get_current_filename() << ":";
	s << yylineno << ":";
	s << yytext << ": ";
	s << "lexical error: ";
	s << str;

	errors++;
	std::cerr << s.str();
	exit(1);
}
void add_to_lookup(std::deque<std::string> filelist, int category) {
	for(int i = 0; i < filelist.size(); ++i)
		ident_table.insert(filelist[i], category, true);
}
std::deque<std::string> get_sysinclude_fstream() {
	std::deque<std::string> s;
	s.push_back("ifstream");
	s.push_back("ofstream");
	s.push_back("fstream");
	return s;
}
std::deque<std::string> get_sysinclude_iostream() {
	std::deque<std::string> s;
	s.push_back("cin");
	s.push_back("cout");
	s.push_back("cerr");
	s.push_back("clog");
	return s;
}
std::deque<std::string> get_sysinclude_string() {
	std::deque<std::string> s;
	s.push_back("string");
	return s;
}


void handle_user_include_file()
{
    /* 
    * Create a new string that contains only the file name to be 
    * included and push it to include_stack so that errors can 
    * eventually report the calling file if include_stack isn't empty.
    */
	std::string include = yytext;
	std::string filename = include.substr(1, (strlen(yytext)-2));

	yyin = fopen(filename.c_str(),"r");
	if (!yyin) {
		lexerr("Cannot open include file '" + filename + "'");
		exit(EXIT_FAILURE);
	}
	else {
		push_include_file(filename);
		yypush_buffer_state(yy_new_buffer(yyin, YY_BUF_SIZE));
	}
}

int check_identifier(std::string str) {
	std::pair<int,bool> lookup = ident_table.lookup_pair(yytext);
	int cat = lookup.first;
	bool namespace_req = lookup.second;
	if(!cat)
		cat = IDENTIFIER;
	if(namespace_req) {
		if(!namespace_std)
			lexerr("'using namespace std' required in 120++");
	}
	create_token(cat);
	return cat;
}

void create_token(int cat, int line, std::string file,
			std::string text, std::string val) {
	
	struct TreeNode* treeptr = new struct TreeNode();
	treeptr->t = new Token(cat, line, file, text, val);
	treeptr->num_kids = 0;
	treeptr->prod_num = -1; /* or `cat`? */
	treeptr->prod_text.clear(); /* or `text`? */
	yylval = treeptr;
}

void create_token(int category) {
	create_token(category, yylineno, get_current_filename(), yytext);
}

/* String literal matching */
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
	create_token(category, yylineno, get_current_filename(),
				token_text, token_val);
}

/* Character literal matching */
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
	create_token(category, yylineno, get_current_filename(),
				token_text, token_val);
}

/* File operations */
std::string get_current_filename() {
	std::string str;
	char *tmp;
	if(!include_stack.empty())
		tmp = strdup(include_stack.front().c_str());
	else
		tmp = strdup(yyfilename.c_str());

	str.assign(basename(tmp));
	free(tmp);
	return str;
}

void push_include_file(std::string inc) {
	include_stack.push_front(inc);
}

void pop_include_file() {
	if(!include_stack.empty())
		include_stack.pop_front();
}

