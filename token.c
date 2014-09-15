/*
 * token.c
 * Ancillary functions for token structures.
 */

#include <stdlib.h> /* for malloc */
#include <stdio.h> /* for perror() */
#include <limits.h> /* for INT_MIN and INT_MAX */
#include <string.h> /* for string functions */
#include "cgram.tab.h" /* get #define constant values */
#include "token.h"

struct token *token_new(int category, int lineno, const char *filename, const char *text) {
	/* allocate memory for a token and then copy the 
	 * fields that were passed in.  Finally set [isf]val 
	 * if necessary.
	 */

	const char *errstr;
	struct token *t = (struct token *) malloc( sizeof(*t) );
	if (t == NULL)
		perror("token memory allocation");

	t->text = (char *) calloc(strlen(text)+1, sizeof(char));
	if(t->text == NULL)
		perror("token text allocation");
	t->filename = (char *) calloc(strlen(filename+1), sizeof(char));
	if(t->filename == NULL)
		perror("token filename allocation");

	t->category = category;
	t->lineno = lineno;
	strcpy(t->text, text);
	strcpy(t->filename, filename);

	if(category == ICON)
		/* TODO: atoi() should not ever return an illegal value
		 * but using strtonum() would be safer and has fewer
		 * undefined conditions.
		 */
		t->ival = atoi(text);

	if (category == CCON) {
		/* should only be a single character matched, but it
		 * will be added by token_set_char().  Allocate two
		 * characters for the null terminator.
		 */
		t->sval = (char *) calloc(2, sizeof(char)); 
	}

	if(category == STRING) {
		/* allocate room for the first quote and null
		 * terminator because rest of string will be added
		 * by token_append_literal().
		 */
		t->sval = (char *) calloc(strlen(text+1), sizeof(char));
		strcpy(t->sval, text);
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
	free(t->sval);
	free(t);
	return;
}

/* TODO: Combine token_append_literal() and token_append_text() into
 * one function and use warappers to call this combined function. */

void token_append_literal(struct token *t, const char *sval) {
	/* 
	 * sval gets appended during string matching because
	 * there are several parts of a string (such as the
	 * beginning quote, characters, escape characters and
	 * the ending quote that all get matched) and yytext
	 * isn't preserved throughout this.
	 */

	int current_length = strlen(t->sval);
	int new_length = strlen(sval);

	//t->sval = (char *) realloc(t->sval, (current_length + new_length + 1));
	t->sval = (char *) realloc(t->sval, (current_length + new_length));
	strncat(t->sval, sval, new_length);
}
void token_append_text(struct token *t, const char *text) {
	/* append the additional text to the text field as well */

	int current_length = strlen(t->text);
	int new_length = strlen(text);
	t->text = (char *) realloc(t->sval, (current_length + new_length));
	strncat(t->text, text, new_length);
}
/*
void token_append_escape(struct token *t, cchar esc) {
	int current_length = strlen(t->sval);
	t->sval = (char *) realloc(t->sval, (current_length + 1));

}
*/
void token_set_char(struct token *t, const char *sval) {
	/* 
	 * sval should only be a single character here
	 * and was allocated by the constructor.
	 */
	strcpy(t->sval, sval);
}