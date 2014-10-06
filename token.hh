/*
 * token.hh
 * Token class for UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
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
				std::string text, std::string sval = "");
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