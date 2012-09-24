#include "linked_list.h"

// This is a convenience function to quickly inspect the contents 
// of a linked list
void 
print_linked_list(linked_list *list)
{
  int i = 0;
  char *element_template = "Element #%d: {key:\"%s\", value: \"%s\"}\n"; 
  while((list)){
    printf(element_template, i, list->kv.key, list->kv.value);
    list = list->next;
    i++;
  }
}

// This function tries to find the parameter "key" in the parameter "list"
// It either returns a linked_list* pointer for subsequent deletes/puts/gets
// or a NULL value if the key cannot be found
linked_list** 
find_key(linked_list **list, char *key)
{
  linked_list **current = list;

  while(*current && strcmp((*current)->kv.key, key)){
    current = &((*current)->next);
  }
  return current;
}

// This function tries to find the key/value pair identified by "key"
// and returns either either:
// - LL_VALUE_FOUND if the key was found in the linked list "l", in which case
//   it also assigns the associated value to "value" before returning
// - LL_VALUE_NOT_FOUND if the "key" parameter can not be found in 
//   the linked list, in which case NULL is assigned to "value" 
ll_status_code
linked_list_get(linked_list *l, char *key, char **value)
{
  linked_list **found = find_key(&l, key);
  if(*found){
    *value = (*found)->kv.value;
    return LL_VALUE_FOUND; 
  }
  else{
    *value = NULL;
    return LL_VALUE_NOT_FOUND; 
  }
}

// This function can either 
// - INSERT a new key/value pair into a linked list
// - UPDATE/PATCH an existing key/value pair with a new value
// 
// Returns either:
// - LL_PUT_OK on a successful UPDATE/PATCH
// -v LL_ENOMEM if it fails to allocate sufficient memory for a 
//   new key/value pair
ll_status_code
linked_list_put(linked_list **list, key_value kv)
{
  char *key = strdup(kv.key);
  if(! key)
    goto bad;
  char *value = strdup(kv.value);
  if(! value)
    goto bad;
  linked_list **found = find_key(list, kv.key);
  
  if(*found){
    free((*found)->kv.value);
    (*found)->kv.value = strdup(kv.value);
    return LL_PUT_OK; 
  }
  else{
    // Just insert the new key/value at HEAD
    linked_list *tmp = *list; 
    *list = malloc(sizeof **list);
    if(! *list)
      goto bad;
    else {
      (*list)->kv.key = key;
      (*list)->kv.value = value;
      (*list)->next = tmp;
      return LL_PUT_OK; 
    }
  } 
bad:
  // TODO: free the memory if needed
  return LL_ENOMEM;
}

ll_status_code 
linked_list_delete(linked_list **list, char *key){
  linked_list **found = find_key(list, key);
  linked_list *cleaner;
  if (*found) {
    cleaner = *found;
    *found = (*found)->next;
    free(cleaner->kv.value);
    free(cleaner->kv.key);
    free(cleaner);
  }
  return LL_DELETE_OK;
}
