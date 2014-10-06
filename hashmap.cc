#include <list>
#include <string>
#include <iostream>
#include "token.hh"
#include "hashmap.hh"

std::list<Token *> hash_table[HASHTABLE_SIZE];

int ht_hash(const char *str) {
	/* 
	 * Modified from sdbm hash found at
	 * http://www.cse.yorku.ca/~oz/hash.html
	 */
	 char *tmp = strdup(str);
	 int hash = 0;
	 int c;

	 while (c = *str++)
	 	hash = c + (hash << 6) + (hash << 16) - hash;

	 free(tmp);
	 /* Because I'm not good at bit-shifting, mod by table size */
	 return hash % HASHTABLE_SIZE; 
}

bool ht_insert(Token *t, int cat) {
	//std::cout << "inserting in hash table " << t->get_text() << std::endl;
	int in_table = ht_lookup(t->get_text().c_str());
	if(!in_table) {
		//std::cout << "was not in table" << std::endl;
		int h = ht_hash(t->get_text().c_str());
		hash_table[h].push_back(t);
		return true;
	} else {
		return false;
	}
}

int ht_lookup(const char *str) {
	//std::cout << "looking up in hash table " << str << std::endl;
	std::list<Token *>::iterator hash_iter;
	int h = ht_hash(str);

	if(!hash_table[h].empty()) {
		hash_iter = hash_table[h].begin();
		for(hash_iter; hash_iter != hash_table[h].end(); ++hash_iter) {
			if(!(*hash_iter)->get_text().compare(str)) {
				return (*hash_iter)->get_category();
			}
		}
	}
	return 0;
}