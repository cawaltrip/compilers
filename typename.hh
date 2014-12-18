/*
 * typename.hh
 * UIdaho CS-445 120++ Compiler
 * TypenameTable and TypenameEntry class header for 120++ compiler
 * 
 * Copyright (C) 2014 Chris Waltrip <walt2178@vandals.uidaho.edu>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TYPENAME_HH_
#define _TYPENAME_HH_

#include <cstddef>
#include <deque>
#include <ostream>
#include <string>
#include <utility>

typedef struct TypenameEntry {
	friend std::ostream & operator<<(std::ostream &os,
						const TypenameEntry &t);
	std::string name;
	int category;
	std::string nspace;
	std::size_t size;

	TypenameEntry(std::string n, int c, std::string ns = "",
						std::size_t s = 8)
			: name(n), category(c), nspace(ns), size(s) {}
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
	TypenameEntry get_entry(TypenameEntry e);
	TypenameTable();
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