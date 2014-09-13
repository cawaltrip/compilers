/*
 * token.c
 * Ancillary functions for token structures.
 */

#include <stdlib.h> /* for malloc */
#include <stdio.h> /* for perror() */
#include <limits.h> /* for INT_MIN and INT_MAX */
#include "cgram.tab.h" /* get #define constant values */
#include "token.h"

struct token *token_new(int category, const char* text, int lineno, const char *filename) {
	/* allocate memory for a token and then copy the 
	 * fields that were passed in.  Finally set [isf]val 
	 * if necessary.
	 */
	 
	const char *errstr;
	struct token *t = malloc(sizeof(*t));
	if (t == NULL)
		perror("token memory allocation");

	t->text = calloc(strlen(text)+1, sizeof(char));
	if(t->text == NULL)
		perror("token text allocation");
	t->filename = calloc(strlen(filename+1), sizeof(char));
	if(t->filename == NULL)
		perror("token filename allocation");

	t->category = category;
	t->lineno = lineno;
	strcpy(t->text, text);
	strcpy(t->filename, filename);

	/* TODO: [isf]val setting */
	if(category == ICON) {
		t->ival = (int)strtonum(text, INT_MIN, INT_MAX, &errstr);
		if(errstr) {
			perror(errstr);
		}
	}
	if(category == CCON) {
		/* remove quotes and escapes and store */
	}

	return t;
}

void token_free(struct token *t) {
	/*
	 * First free the internal components that had memory
	 * allocated to them and then free the token itself.
	 */

	 free(t->text);
	 free(t->filename);
	 free(t);

	 return;
}






