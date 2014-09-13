/* 
 * token.h
 * Define the token structure that will be used
 */

#ifndef _TOKEN_H_
#define _TOKEN_H_

struct token {
	int category;
	char *text;
	int lineno;
	char *filename;
	int ival;
	char *sval;
	double fval;
 }

/* constructor for a new token */
struct token *token_new(int category, const char *text, const char* filename);

/* deconstructor for a given token - free() doesn't return 
 * a value so return void.
 */
void token_free(struct *token);

#endif _TOKEN_H_