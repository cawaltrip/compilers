#ifndef _TYPENAME_HH_
#define _TYPENAME_HH_

#include <cstddef>
#include <deque>
#include <string>
#include <utility>

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
	static const size_t HASHTABLE_SIZE = 137;
	std::deque<TypenameEntry> bucket[HASHTABLE_SIZE];
	std::size_t hash(std::string name);
public:
	bool insert(std::string name, int cat, std::string nspace = "");
	int lookup(std::string name);
	std::pair<int,std::string> lookup_namespace(std::string name);
	TypenameEntry get_entry(std::string name);
};

/*
 * Direct comparison operators for between TypenameEntry objects and either 
 * other TypenameEntry objects or std::strings directly.
 */
inline bool operator==(const TypenameEntry& lhs, const std::string& rhs) { 
	return (lhs.name == rhs);
}
inline bool operator!=(const TypenameEntry& lhs, const std::string& rhs) { 
	return !(lhs.name == rhs);
}
inline bool operator==(const TypenameEntry& lhs, const TypenameEntry& rhs) { 
	return (lhs == rhs.name);
}
inline bool operator!=(const TypenameEntry& lhs, const TypenameEntry& rhs) { 
	return !(lhs == rhs.name);
}



#endif /* _TYPENAME_HH_ */