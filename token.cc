/*
 * token.cc
 * UIdaho CS-445 120++ Compiler
 * Token class implementation for 120++ compiler
 * 
 * Copyright (C) 2014 Chris Waltrip <walt2178@vandals.uidaho.edu>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include "120gram.tab.h"
#include "token.hh"

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
void Token::set_category(int category) {
	this->category = category;
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
