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

/* deconstructor for a given token - free() doesn't return */
void token_free(struct token *t);

/* append a portion of a string literal */
void token_append_literal(struct token *t, const char *sval);

/* append a portion of string literal to text field */
void token_append_text(struct token *t, const char *text);

/* set a character constant */
void token_set_char(struct token *t, const char *sval);

#endif /* _TOKEN_H_ */