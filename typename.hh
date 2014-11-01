#ifndef _TYPENAME_HH_
#define _TYPENAME_HH_

#include <deque>
#include <string>

typedef struct TypenameEntry {
	std::string name;
	int category;
	std::string nspace;
	TypenameEntry(std::string name, int cat, std::string nspace = "") {
		this->name = name;
		this->category = cat;
		this->nspace = nspace;
	}
} TypenameEntry;

class TypenameTable {
private:
	static const int HASHTABLE_SIZE = 137;
	std::deque<TypenameEntry> bucket[HASHTABLE_SIZE];
	int hash(std::string name);
public:
	bool insert(std::string name, int cat, std::string nspace = "");
	int lookup(std::string name);
	std::pair<int,std::string> lookup_namespace(std::string name);
};

#endif /* _HASHMAP_HH_ */