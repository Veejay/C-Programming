#include "hash_table.h"

// Allocates a new hash table with the given number of buckets
// and returns a pointer to that hash table
hashtable* 
new_hash_table(int num_buckets)
{
  hashtable *ht = malloc(sizeof(*ht));
  
  // TODO: If allocation failed, return the proper status code, see 
  // hash_table_allocation_status in header file
  
  ht->size = num_buckets;
  ht->table = malloc(num_buckets * sizeof(*ht->table)); 
  
  return ht;
}

// FIXME: Implementation is naive for now
int 
hash(char *key, int size)
{
  int r, hash;
  while((r = *key++)){
    hash += r;
  }
  return hash % size;
}

int 
put(hashtable *ht, key_value kv)
{
  char *key = kv.key; 
  int hashed_value = hash(key, ht->size);

  return linked_list_put(&(ht->table[hashed_value]), kv);
}

key_value 
get(hashtable *ht, char *key)
{
  int hashed_value = hash(key, ht->size); 
  return linked_list_get(ht->table[hashed_value], key);
} 

int 
destroy(hashtable *ht, char *key)
{
  int hashed_value = hash(key, ht->size); 
  return linked_list_delete(&(ht->table[hashed_value]), key); 
}
