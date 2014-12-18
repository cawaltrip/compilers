/*
 * token.hh
 * UIdaho CS-445 120++ Compiler
 * Token class for 120++ compiler
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

#ifndef _TOKEN_HH_
#define _TOKEN_HH_

#include <string>

class Token {
private:
	/* these values are always set */
	int category;
	int lineno;
	std::string filename;
	std::string text;
	
	/* these values are conditionally set depending on category */
	int ival;
	std::string sval;
	char cval;
	double fval;

public:
	/* Token(); */
	Token(int category, int lineno, std::string filename,
				std::string text = "", std::string sval = "");
	int get_category();
	void set_category(int category);
	int get_lineno();
	std::string get_filename();
	
	/* text actions */
	void append_text(std::string text);
	std::string get_text();

	/* ival actions */
	int get_ival();

	/* fval actions */
	int get_fval();

	/* sval actions */
	void append_sval(std::string sval);
	std::string get_sval();
	
	/* cval actions */
	void set_cval(char cval);
	char get_cval();
};

#endif /* _TOKEN_HH_ */