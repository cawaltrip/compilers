/* typename.cc
 * TypenameTable and TypenameEntry class implementation for 
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#include <deque>
#include <string>
#include <iostream>
#include "typename.hh"

int TypenameTable::hash(std::string name) {
	/* 
	 * This code is based on a post from StackOverflow:
	 * http://stackoverflow.com/a/107657/2592570
	 */
	unsigned int hash = 0;
	const char* s = name.c_str();
	while(*s) {
		hash = hash * 101 + *s++;
	}
	return hash % HASHTABLE_SIZE;
}


bool TypenameTable::insert(std::string name, int cat, std::string nspace) {
	/* 
	 * If the item is not in the lookup table already then add it.
	 * Return true if insert is successful and false otherwise.
	 */
	if(!this->lookup(name)) {
		int h = this->hash(name);
		TypenameEntry item(name, cat, nspace);
		this->bucket[h].push_back(item);
		if(this->lookup(name)) /* could check error code */
			return true;
	}
	return false;
}
/* 
 * Use this function when we only care about the category and
 * not whether the namespace matters
 */
int TypenameTable::lookup(std::string name) {
	return this->lookup_namespace(name).first;
}
/* 
 * Return both the category and whether this identifier requires
 * the standard namespace.
 */
std::pair<int,std::string> TypenameTable::lookup_namespace(std::string name) {
	int h = this->hash(name);
	std::pair<int,std::string> pair = std::make_pair(0,"");
	std::deque<TypenameEntry> b = this->bucket[h];
	std::deque<TypenameEntry>::iterator i;
	for(i = b.begin(); i != b.end(); ++i) {
		if(!name.compare(i->name)) {
			pair.first = i->category;
			pair.second = i->nspace;
		}
	}
	return pair;
}