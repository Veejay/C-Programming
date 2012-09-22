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
  int i;
  for(i = 0; i < num_buckets; i++){
    ht->table[i] = NULL;
  }
  return ht;
}

// FIXME: Implementation is naive for now
unsigned int 
hash(char *key, int size)
{
  unsigned int r = 0u, hash = 0u;
  while((r = *key++)){
    hash += r;
  }
  return (hash % size);
}

int 
put(hashtable *ht, key_value kv)
{
  char *key = kv.key; 
  unsigned int hashed_value = hash(key, ht->size);

  return linked_list_put(&(ht->table[hashed_value]), kv);
}

int 
get(hashtable *ht, char *key, char **result)
{
  unsigned int hashed_value = hash(key, ht->size); 
  if(linked_list_get(ht->table[hashed_value], key, result) == 0) {
    return 0; 
  }
  else {
    return -1; 
  }
} 

int 
destroy(hashtable *ht, char *key)
{
  unsigned int hashed_value = hash(key, ht->size); 
  return linked_list_delete(&(ht->table[hashed_value]), key); 
}
