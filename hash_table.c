#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LL_KEY_NOT_FOUND 99;
#define LL_DELETE_OK 0;
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

int has_key(linked_list *list, char *key)
{
  return list && (strcmp(list->kv.key, key) == 0);
}

int linked_list_delete(linked_list **l, char *key)
{
  // Saving that for later, don't know if it's necessary :/
  linked_list *head = *l;
  
  // As long as we don't find the key and the end of the list
  // hasn't been reached, keep going forward
  while((*l) && !has_key((*l), key)){
    (*l) = (*l)->next;
  }
  // We've reached the end of the list but the key still doesn't match
  // it's a no show
  if(!has_key((*l), key)){
    return LL_KEY_NOT_FOUND;
  }
  // There's a match for the key, we need to copy the content of the next node
  // into the current one and remove that next node for good
  else{ 
    if((*l)->next){
      linked_list *tmp = (*l)->next;
      (*l)->kv = tmp->kv;
      (*l)->next = tmp->next;
      free(tmp);
      *l = head;
    }
    else{
    }
    return LL_DELETE_OK;
  }
}

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
  return linked_list_insert(&(ht->table[hashed_value]), kv);
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
  return linked_list_delete(&(ht->table[hashed_value]), key); 
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
  key_value kv3 = {.key="Kim", .value="Nguyen"};
  key_value kv4 = {.key="Sylvain", .value="Lebresne"};
  key_value kv5 = {.key="Ignacy", .value="Gawedzki"};
  key_value kv6 = {.key="Cédric", .value="Miachon"};

  linked_list *l = NULL;

  linked_list_insert(&l, kv1);
  linked_list_insert(&l, kv4);
  linked_list_insert(&l, kv5);
  linked_list_insert(&l, kv6);
  linked_list_insert(&l, kv2);
  linked_list_insert(&l, kv3);

  print_linked_list(l);

  printf("=========================\n");
  printf("VALUE FOR KEY Bertrand: %s\n", linked_list_get(l, "Bertrand").value);
  printf("=========================\n");

  printf("DELETING ELEMENT WITH KEY Cédric\n");
  linked_list_delete(&l, "Cédric");
  
  printf("DELETING ELEMENT WITH KEY Guillaume\n");
  linked_list_delete(&l, "Guillaume");

  
  printf("DELETING ELEMENT WITH KEY Bertrand\n");
  linked_list_delete(&l, "Bertrand");

  printf("\n=========================\n");
  print_linked_list(l);

  return 0;
}
