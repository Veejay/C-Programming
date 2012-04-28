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
  linked_list *head = *l;
  linked_list *prev;
  
  // The key we're looking for is at head, special case
  if(has_key(*l, key)){
    linked_list *cleaner = *l;
    *l = (*l)->next;
    free(cleaner);
    return LL_DELETE_OK;
  }

  while((*l) && !has_key((*l), key)){
    prev = *l;
    (*l) = (*l)->next;
  }
  // Reached end of the list, no show
  if(!has_key((*l), key)){
    *l = head;
    return LL_KEY_NOT_FOUND;
  }
  else{ 
    if((*l)->next){
      linked_list *tmp = *l;
      prev->next = (*l)->next;
      free(tmp);
    }
    // Special case if the element to delete is the last element
    else{
      free(prev->next);
      prev->next = NULL; 
    }
    *l = head;
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
  key_value kv5 = {.key="Ignacy", .value="Gawędzki"};
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

  printf("DELETING ELEMENT WITH KEY foobar\n");
  linked_list_delete(&l, "foobar");
  
  printf("DELETING ELEMENT WITH KEY moobar\n");
  linked_list_delete(&l, "moobar");

  printf("We just deleted two values that didn't exist in the list\n");
  printf("\n=========================\n");
  print_linked_list(l);
  
  printf("\n=========================\n");
  printf("DELETING ELEMENT WITH KEY Kim\n");
  linked_list_delete(&l, "Kim");
  print_linked_list(l);

  printf("DELETING ELEMENT WITH KEY Bertrand\n");
  linked_list_delete(&l, "Bertrand");
  printf("\n=========================\n");
  print_linked_list(l);
  return 0;
}
