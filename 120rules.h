/* Token type.  */
#ifndef YY_PRODUCTION_RULES
#define YY_PRODUCTION_RULES

#include <string>

typedef struct yyrule { 
	int num;
	std::string text;
	yyrule(int n, std::string s) : num(n), text(s) { }
} yyrule;

const struct yyrule START_RULE(10000,"Start Symbol");

const struct yyrule LITERAL_1(11001,"Integer Literal");
const struct yyrule LITERAL_2(11002,"Character Literal");
const struct yyrule LITERAL_3(11003,"Floating Literal");
const struct yyrule LITERAL_4(11004,"String Literal");
const struct yyrule LITERAL_5(11005,"Boolean Literal");




#endif /* YY_PRODUCTION_RULES */