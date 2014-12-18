/*
 * exception.hh
 * UIdaho CS-445 120++ Compiler
 * Exception classes for use throughout compiler
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