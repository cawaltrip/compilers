#include <deque>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "hashmap.hh"

int HashTable::hash(std::string name) {
	/* 
	 * This code is based on a post from StackOverflow:
	 * http://stackoverflow.com/a/107657/2592570
	 */
	unsigned long hash = 0;
	std::string::iterator i = name.begin();
	while(i != name.end()) {
		hash = hash * 101 + i++;
	}
	return hash % this->HASHTABLE_SIZE;
}

bool HashTable::insert(std::string name, int category) {
	/* 
	 * If the item is not in the lookup table already then add it.
	 * Return true if insert is successful and false otherwise.
	 */
	if(!this->lookup(name)) {
		int h = this->hash(name);
		this->bucket[h].insert(new HashBucket(name, category));
		if(this->lookup(name)) { /* could check error code */
			return true;
		}
	}
	return false;
}
int HashTable::lookup(std::string name) {
	int h = this->hash(name);
	int category = 0;
	std::deque<HashBucket> b = this->bucket[h];
	std::deque<HashBucket>::iterator i;
	for(i = b.begin(); i != b.end(); ++i) {
		if(!name.compare(i->name))
			category = i->category();
	}
	return category;
}