/* exception.hh
 * Basic exception class for various errors
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#ifndef _EXCEPTION_HH_
#define _EXCEPTION_HH_

#include <exception>
#include <sstream>
#include <string>

/*
 * The basis of this class is based on a post from StackOverflow:
 * http://stackoverflow.com/a/8152888/2592570
 */
class Exception : public std::exception {
protected:
	std::string err_msg;
public:
	explicit Exception(const char* message): err_msg(message) {}
	explicit Exception(const std::string& message): err_msg(message) {}
	virtual ~Exception() throw (){}

	virtual const char* what() const throw () {
		std::stringstream ss;
		ss << "120++ Error: " << err_msg;
		return ss.str().c_str();
	}
};

class EHaltCommandLineParse : public Exception {
public:
	EHaltCommandLineParse() : Exception("Stopped parsing command line") {}
};

class ENoTypenameEntry : public Exception {
public:
	ENoTypenameEntry() 
		: Exception("Semantic: Typename Entry not found") {}
};

class ENoSymbolEntry : public Exception {
public:
	ENoSymbolEntry() :
		Exception("Semantic: Symbol Entry not found") {}
};

class EDuplicateSymbol : public Exception {
public:
	EDuplicateSymbol() : Exception("Semantic: Symbol already " \
					"exists in Symbol Table") { }
};

class EBadGrammarParse : public Exception {
public:
	EBadGrammarParse() 
		: Exception("Semantic: Unexpected grammar rule parse") {}
};

class ENullTokenAccess : public Exception {
public:
	ENullTokenAccess()
		: Exception("Semantic: Tree Node is not a leaf (no token)") {}
};

class ENullSymbolTableAccess : public Exception {
public:
	ENullSymbolTableAccess()
		: Exception("Semantic: Symbol table does not exist") {}
};

class ESymbolTableNestedTooDeep : public Exception {
public:
	ESymbolTableNestedTooDeep() 
		: Exception("Semantic: Cannot nest symbol table") {}
};
#endif /* _EXCEPTION_HH_ */