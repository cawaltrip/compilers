/* token.cc
 * Token class implementation for UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#include "token.hh"

Token::Token(int category, int lineno, string filename, string text) {
	this.category = category;
	this.lineno = lineno;
	this.filename = filename;
	this.text = text;

	switch(category) {
		case ICON:
			this.ival = atoi(text);
			break;
		case FCON:
			this.fval = 0.0;
			break;
		case CCON:
			this.cval = text.at(0); /* try/catch - out_of_range */
			break;
		case STRING:
			this.sval = text; /* should just be a double-quote */
			break;
	}
}

void Token::append_sval(string sval) {
	return;
}
void Token::set_cval(char cval) {
	return;
}
void Token::append_text(string text) {
	return;
}