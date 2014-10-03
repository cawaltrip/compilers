/* token.cc
 * Token class implementation for UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#include <cstdlib>
#include "120gram.tab.h"
#include "token.hh"

/*
Token::Token() {
	this->category = -1;
}
*/
Token::Token(int category, int lineno, std::string filename,
				std::string text, std::string sval) {
	this->category = category;
	this->lineno = lineno;
	this->filename = filename;
	this->text = text;

	/* empty initialization */
	this->ival = 0;
	this->sval = "";
	this->cval = '\0';
	this->fval = 0.0;

	/* actual initialization */
	switch(category) {
		case INTEGER:
			/* use std::stoi if c++11 is supported */
			this->ival = atoi(text.c_str());
			break;
		case FLOATING:
			/* use errno */
			this->fval = strtod(text.c_str(), NULL);
			break;
		case CHARACTER:
		case STRING:
			this->sval = sval;
			break;
	}
}

int Token::get_category() {
	return this->category;
}

int Token::get_lineno() {
	return this->lineno;
}

std::string Token::get_filename() {
	return this->filename;
}
	
/* text actions */
void Token::append_text(std::string text) {
	this->text.append(text);
	return;
}

std::string Token::get_text() {
	return this->text;
}

/* ival actions */
int Token::get_ival() {
	return this->ival;
}

/* fval actions */
int Token::get_fval() {
	return this->fval;
}

/* sval actions */
void Token::append_sval(std::string sval) {
	this->sval.append(sval);
	return;
}
std::string Token::get_sval() {
	return this->sval;
}
	
/* cval actions */
void Token::set_cval(char cval) {
	this->cval = cval;
	return;
}

char Token::get_cval() {
	return this->cval;
}
