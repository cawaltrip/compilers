#ifndef _HASHMAP_HH_
#define _HASHMAP_HH_

#include <deque>
#include <string>

//#define HASHTABLE_SIZE 137

typedef struct HashBucket {
	std::string name;
	int category;
	HashBucket(std::string n, int c) : name(n), category(c) { }
} HashBucket;

class HashTable {
private:
	static const int HASHTABLE_SIZE = 137;
	std::deque<HashBucket> bucket[HASHTABLE_SIZE];
	int hash(std::string name);
public:
	bool insert(std::string name, int category);
	int lookup(std::string name);
};

#endif /* _HASHMAP_HH_ */