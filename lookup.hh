#ifndef _HASHMAP_HH_
#define _HASHMAP_HH_

#include <deque>
#include <string>

//#define HASHTABLE_SIZE 137

typedef struct LookupBucket {
	std::string name;
	int category;
	bool namespace_req;
	LookupBucket(std::string n, int c, bool b = false) {
		name = n;
		category = c;
		namespace_req = b;
	}
} LookupBucket;

class LookupTable {
private:
	static const int HASHTABLE_SIZE = 137;
	std::deque<LookupBucket> bucket[HASHTABLE_SIZE];
	int hash(std::string name);
public:
	bool insert(std::string name, int category, bool nspace = false);
	int lookup(std::string name);
	std::pair<int,bool> lookup_pair(std::string name);
};

#endif /* _HASHMAP_HH_ */