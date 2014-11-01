/* exception.hh
 * Basic exception class for various errors
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#ifndef _EXCEPTION_HH_
#define _EXCEPTION_HH_

#include <exception>
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
		return err_msg.c_str();
	}
};

class EBadTypenameEntry : public Exception {
public:
	EBadTypenameEntry() : Exception("Typename Entry not found") {}
};

#endif /* _EXCEPTION_HH_ */