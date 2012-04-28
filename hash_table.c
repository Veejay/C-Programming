#include "hash_table.h"

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
