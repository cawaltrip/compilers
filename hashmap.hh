#ifndef _HASHMAP_HH_
#define _HASHMAP_HH_

#include <list>

#define HASHTABLE_SIZE 137

int ht_hash(const char *str);
bool ht_insert(Token *t, int cat);
int ht_lookup(const char *str);

#endif /* _HASHMAP_HH_ */