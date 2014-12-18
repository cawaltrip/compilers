/*
 * typename.cc
 * UIdaho CS-445 120++ Compiler
 * TypenameTable and TypenameEntry class implementation for 120++ compiler
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

#include <iostream>

#include "120gram.tab.h"
#include "typename.hh"
#include "exception.hh"

std::ostream &operator<<(std::ostream &os, const TypenameEntry &t) {
	if(t.nspace != "") {
		os << t.nspace << "::";
	}
	os << t.name;

	return os;
}

/* Add primitives when creating new TypenameTable */
TypenameTable::TypenameTable() {
	this->insert("int", INT);
	this->insert("char", CHAR);
	this->insert("float", FLOAT);
	this->insert("double", DOUBLE); /* May remove this token */
	this->insert("long", INT); /* Fixes issues calling longs and shorts */
	this->insert("short", INT);
}

std::size_t TypenameTable::hash(std::string name) {
	/* 
	 * This code is based on a post from StackOverflow:
	 * http://stackoverflow.com/a/107657/2592570
	 */
	std::size_t hash = 0;
	const char* s = name.c_str();
	while(*s) {
		hash = hash * 101 + *s++;
	}
	return hash % this->HASHTABLE_SIZE;
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
 * not whether the namespace matters.
 *
 * TODO: Rename to lookup_category()
 */
int TypenameTable::lookup(std::string name) {
	return this->lookup_namespace(name).first;
}
/* 
 * Return both the category and whether this identifier requires
 * the standard namespace.
 */
std::pair<int,std::string> TypenameTable::lookup_namespace(std::string name) {
	std::pair<int, std::string> pair;
	try {
		TypenameEntry te = this->get_entry(name);
		pair = std::make_pair(te.category, te.nspace);
	} catch(ENoTypenameEntry e) {
		pair = std::make_pair(0,"");
	}
	return pair;
}

TypenameEntry TypenameTable::get_entry(std::string name) {
	std::size_t h = this->hash(name);
	std::deque<TypenameEntry> b = this->bucket[h];
	std::deque<TypenameEntry>::iterator it;
	for(it = b.begin(); it != b.end(); ++it) {
		std::size_t i = it - b.begin();
		if(b[i] == name) {
			return b[i];
		}
	}
	throw ENoTypenameEntry();
}

TypenameEntry TypenameTable::get_entry(TypenameEntry e) {
	try {
		return this->get_entry(e.name);	
	} catch (ENoTypenameEntry ex) {
		throw ENoTypenameEntry();
	}
	
}
