#include "hash_table.h"

// Allocates a new hash table with the given number of buckets and 
// assigns the space to the hashtable** ht parameter for later use. 
// In case sufficient memory cannot be allocated, returns a HT_ENOMEM
// (see hash_table.h)
ht_status_code
new_hash_table(int num_buckets, hashtable **ht)
{
  hashtable *h = *ht; // One less indirection, easier to grok 
  int i;

  h = malloc(sizeof *h);
  if(! h)
    goto bad; 

  h->size = num_buckets;
  h->table = malloc(num_buckets * sizeof *h->table); 
  if(! h->table)
    goto bad; 

  for(i = 0; i < num_buckets; i++){
    h->table[i] = NULL;
  }
  return HT_CREATE_OK; 

bad:
  if(h){ // Couldn't allocate memory for the buckets 
    free(h);
  }
  return HT_ENOMEM;
}

// This function is used internally to compute the number of the bucket
// where a given key/value pair should be stored.
// FIXME: Find better implementation 
static unsigned int 
hash(char *key, int size)
{
  unsigned int r = 0u, hash = 0u;
  while((r = *key++)){
    hash += r;
  }
  return (hash % size);
}

// This function can either:
// - CREATE a key/value pair in the given hash table
// - UPDATE/PATCH a pre-existing key/value pair with a new value
// It delegates to hash and linked_list_put and returns one of the status
// codes defined in hash_table.h
ht_status_code
put(hashtable *ht, key_value kv)
{
  char *key = kv.key; 
  unsigned int hashed_value = hash(key, ht->size);

  ll_status_code sc = linked_list_put(&(ht->table[hashed_value]), kv);

  // GOD, THAT IS ONE UGLY-ASS PATTERN :/
  switch(sc){
    case LL_PUT_OK:
      return HT_PUT_OK;
    case LL_ENOMEM:
      return HT_ENOMEM;
    default:
      return HT_UNKNOWN_ERROR;
  }
}
// This function tries to find the key/value pair identified by "key"
// (by delegating to linked_list_get) and returns either:
// - HT_VALUE_FOUND if the key was found in the hash table ht, in which case
//   it also assigns the associated value to "result" before returning
// - HT_VALUE_NOT_FOUND if the "key" parameter can not be found in 
//   the hash table "ht", in which case NULL is assigned to "value" 
ht_status_code
get(hashtable *ht, char *key, char **result)
{
  unsigned int hashed_value = hash(key, ht->size); 
  ll_status_code sc = linked_list_get(ht->table[hashed_value], key, result);
  switch(sc){
    case LL_VALUE_FOUND:
      return HT_VALUE_FOUND; 
    case LL_VALUE_NOT_FOUND:
      return HT_VALUE_NOT_FOUND;
  }
} 

ht_status_code
destroy(hashtable *ht, char *key)
{
  unsigned int hashed_value = hash(key, ht->size); 
  linked_list_delete(&(ht->table[hashed_value]), key); 
  return HT_DELETE_OK;
}
