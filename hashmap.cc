#include <deque>
#include <string>
#include <iostream>
#include "hashmap.hh"

int HashTable::hash(std::string name) {
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


bool HashTable::insert(std::string name, int category) {
	/* 
	 * If the item is not in the lookup table already then add it.
	 * Return true if insert is successful and false otherwise.
	 */
	std::cout << "Starting Insert for: " << name << std::endl;
	if(!this->lookup(name)) {
		std::cout << "  lookup not found - inserting." << std::endl;
		int h = this->hash(name);
		std::cout << "  hash: " << h << std::endl;
		HashBucket item(name, category);
		this->bucket[h].push_back(item);
		std::cout << "  item added to bucket" << std::endl;
		if(this->lookup(name)) { /* could check error code */
			std::cout << "  lookup found after add" << std::endl;
			return true;
		} else {
			std::cout << "  lookup FAILED after add" << std::endl;
		}
	} else {
		std::cout << "  lookup FAILED" << std::endl;
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
			category = i->category;
	}
	return category;
}