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
	string filename;
	string text;
	
	/* these values are conditionally set depending on category */
	int ival;
	string sval;
	char cval;
	double fval;

public:
	Token(int category, int lineno, string filename, string text);
	~Token();
	int get_category()
		return this.category;
	int get_lineno()
		return this.lineno;
	string get_filename()
		return this.filename;
	char* get_filename()
		return this.filename.c_str();
	
	/* text actions */
	void append_text(string text);
	string get_text()
		return this.text;
	char* get_text()
		return this.text.c_str();

	/* ival actions */
	int get_ival()
		return this.ival;
	/* fval actions */
	int get_fval()
		return this.fval;
	/* sval actions */
	void append_sval(string sval);
	string get_sval()
		return this.sval;
	char* get_sval()
		return this.sval.c_str();
	
	/* cval actions */
	void set_cval(char cval);
	char get_cval()
		return this.cval;
};

#endif /* _TOKEN_HH_ */