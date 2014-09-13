/* 
 * token.h
 * Define the token structure that will be used
 */

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "cgram.tab.h"

struct token {
	int category;
	int lineno;
	char *filename;
	char *text;
	int ival;
	char *sval;
	double fval;
 };

/* constructor for a new token */
struct token *token_new(int category, int lineno, const char *filename, const char *text);

/* deconstructor for a given token - free() doesn't return 
 * a value so return void.
 */
void token_free(struct token *t);

#endif /* _TOKEN_H_ */