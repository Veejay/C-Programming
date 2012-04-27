#include <stdio.h>
#include <stdlib.h>

/*************************** DATA STRUCTURES **************************/

typedef struct key_value{
  char *key;
  char *value;
} key_value;

typedef struct linked_list {
  key_value kv; 
  struct linked_list *next;
} linked_list;

typedef struct hashtable {
  int size;
  linked_list *table[];
} hashtable;

/*************************** FUNCTIONS ********************************/

// This is the epicenter of all the hash operations
// FIXME: Implementation is naive for now
int hash(char *key, int size){
  int r, hash;
  while((r = *key++)){
    hash += r;
  }
  return hash % size;
}

/*
 *
 * ACCESS OPERATIONS
 *
 *
 */

// Store an element in the hashtable.
// Should return a status code to give information about the operation I guess...
// If the key already exists in the hash table, updates the record 
// If it doesn't, stores it
int put(hashtable *ht, key_value* kv)
{
  // First we need to determinate the proper hash for that key/value pair
  char *key = kv->key; 
  int hash = hash(key, ht->size);

  // Now we can access the proper bucket and store the data
  
}

// Retrieves the key_value stored in the hash table based on the key hash
key_value* get(hash_table *ht, char *key)
{
  // CODE HERE
} 

// Deletes the record associated to the key in the hash table
int delete(hash_table *ht, char *key)
{

}

/************************* HELPERS ************************************/

int linked_list_insert(linked_list *list, key_value* kv){
}

/**********************************************************************/

int main()
{
  return 0;
}
