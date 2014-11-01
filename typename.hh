#ifndef _TYPENAME_HH_
#define _TYPENAME_HH_

#include <deque>
#include <string>

typedef struct TypenameBucket {
	std::string name;
	int category;
	bool namespace_req;
	TypenameBucket(std::string n, int c, bool b = false) {
		name = n;
		category = c;
		namespace_req = b;
	}
} TypenameBucket;

class TypenameTable {
private:
	static const int HASHTABLE_SIZE = 137;
	std::deque<TypenameBucket> bucket[HASHTABLE_SIZE];
	int hash(std::string name);
public:
	bool insert(std::string name, int category, bool nspace = false);
	int lookup(std::string name);
	std::pair<int,bool> lookup_pair(std::string name);
};

#endif /* _HASHMAP_HH_ */