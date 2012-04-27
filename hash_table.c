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

// Store an element in the hashtable.
// Should return a status code to give information about the operation I guess...
// If the key already exists in the hash table, updates the record 
// If it doesn't, stores it
int put(hashtable *ht, key_value kv)
{
  // First we need to determinate the proper hash for that key/value pair
  char *key = kv.key; 
  int hashed_value = hash(key, ht->size);
  
  // Now we can access the proper bucket and store the data
  return linked_list_insert(ht->table[hashed_value], kv);
}

// Retrieves the key_value stored in the hash table based on the key hash
key_value get(hashtable *ht, char *key)
{
  int hashed_value = hash(key, ht->size); 
  return linked_list_get(ht->table[hashed_value], key);
} 

// Deletes the record associated to the key in the hash table
int delete(hashtable *ht, char *key)
{
  int hashed_value = hash(key, ht->size); 
  return linked_list_delete(ht->table[hashed_value], key); 
}

/************************* HELPERS ************************************/

int linked_list_insert(linked_list **list, key_value kv){
  linked_list *tmp = *list; 
  *list = malloc(sizeof(linked_list));
  (*list)->kv = kv;
  (*list)->next = tmp;
  return 0; 
}

key_value linked_list_get(linked_list *l, char *key)
{
  while(strcmp(l->kv.key, key) != 0){
    l = l->next;
  }
  return l->kv;
}

int linked_list_delete(linked_list *l, char *key)
{
  while(l->next != NULL && strcmp(l->kv.key, key) != 0){
    l = l->next;
  }
  if(l->next == NULL && (strcmp(l->kv.key, key) != 0)){
    return LL_KEY_NOT_FOUND;
  }
  else{
    linked_list *tmp = l->next;
    l->kv = tmp->kv;
    l->next = tmp->next;
    free(tmp);
    return LL_DELETE_OK;
  }
}

// Mainly used for testing of insert function
void print_linked_list(linked_list *list)
{
  int i = 0;
  while((list)){
    printf("Element #%d: {key:\"%s\", value: \"%s\"}\n", i, list->kv.key, list->kv.value);
    list = list->next;
    i++;
  }
}

/**********************************************************************/

int main()
{
  key_value kv1 = {.key="Bertrand", .value="Chardon"};
  key_value kv2 = {.key="Guillaume", .value="Leconte"};
  linked_list *l = NULL;
  linked_list_insert(&l, kv1);
  linked_list_insert(&l, kv2);
  print_linked_list(l);
  return 0;
}
