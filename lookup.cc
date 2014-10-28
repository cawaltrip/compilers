/* hashmap.cc
 * LookupTable and LookupBucket class implementation for 
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#include <deque>
#include <string>
#include <iostream>
#include "hashmap.hh"

int LookupTable::hash(std::string name) {
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


bool LookupTable::insert(std::string name, int category, bool namespace_req) {
	/* 
	 * If the item is not in the lookup table already then add it.
	 * Return true if insert is successful and false otherwise.
	 */
	if(!this->lookup(name)) {
		int h = this->hash(name);
		LookupBucket item(name, category, namespace_req);
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
int LookupTable::lookup(std::string name) {
	return this->lookup_pair(name).first;
}
/* 
 * Return both the category and whether this identifier requires
 * the standard namespace.
 */
std::pair<int,bool> LookupTable::lookup_pair(std::string name) {
	int h = this->hash(name);
	std::pair<int,bool> pair = std::make_pair(0,false);
	std::deque<LookupBucket> b = this->bucket[h];
	std::deque<LookupBucket>::iterator i;
	for(i = b.begin(); i != b.end(); ++i) {
		if(!name.compare(i->name)) {
			pair.first = i->category;
			pair.second = i->namespace_req;
		}
	}
	return pair;
}