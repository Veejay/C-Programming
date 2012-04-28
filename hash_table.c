#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

typedef struct hashtable {
  int size;
  linked_list *table[];
} hashtable;


/*************************** FUNCTIONS ********************************/
// This is the epicenter of all the hash operations
// FIXME: Implementation is naive for now
int hash(char *key, int size)
{
  int r, hash;
  while((r = *key++)){
    hash += r;
  }
  return hash % size;
}

int put(hashtable *ht, key_value kv)
{
  char *key = kv.key; 
  int hashed_value = hash(key, ht->size);

  return linked_list_put(&(ht->table[hashed_value]), kv);
}

key_value get(hashtable *ht, char *key)
{
  int hashed_value = hash(key, ht->size); 
  return linked_list_get(ht->table[hashed_value], key);
} 

int destroy(hashtable *ht, char *key)
{
  int hashed_value = hash(key, ht->size); 
  return linked_list_delete(&(ht->table[hashed_value]), key); 
}
