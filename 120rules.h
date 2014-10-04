/* Token type.  */
#ifndef YY_PRODUCTION_RULES
#define YY_PRODUCTION_RULES

#include <string>

typedef struct yyrule { 
	int num;
	std::string text;
	yyrule(int n, std::string s) : num(n), text(s) { }
} yyrule;

struct yyrule PRODUCTION_RULE_1(10001,"Production Rule 1");
struct yyrule PRODUCTION_RULE_2(10002,"Production Rule 2");
struct yyrule PRODUCTION_RULE_3(10003,"Production Rule 3");
struct yyrule PRODUCTION_RULE_4(10004,"Production Rule 4");


#endif /* YY_PRODUCTION_RULES */