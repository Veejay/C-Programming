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
  /* char *key = kv->key; */ 
  /* int hashed_value = hash(key, ht->size); */

  // Now we can access the proper bucket and store the data
  return 0; 
}

// Retrieves the key_value stored in the hash table based on the key hash
key_value* get(hashtable *ht, char *key)
{
  return NULL; 
} 

// Deletes the record associated to the key in the hash table
int delete(hashtable *ht, char *key)
{
  return 0; 

}

/************************* HELPERS ************************************/

int linked_list_insert(linked_list *list, key_value kv){
  linked_list *head = malloc(sizeof(linked_list));
  head->kv = kv;
  head->next = list;
  list = head;
  free(head);
  return 0;
}

// Mainly used for testing of insert function
void print_linked_list(linked_list *list)
{
  int i = 0;
  while((list)){
    printf("Element #%d: %s\n", i, list->kv.value);
    list = list->next;
    i++;
  }
}

/**********************************************************************/

int main()
{
  key_value kv1 = {.key="foo", .value="Bertrand Chardon"};
  key_value kv2 = {.key="goo", .value="Bertrand Chrdon"};
  key_value kv3 = {.key="hoo", .value="Bertrand hardon"};

  linked_list *l = NULL;

  linked_list_insert(l, kv1);
  print_linked_list(l); 

  return 0;
}
