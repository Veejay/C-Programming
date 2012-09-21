#include "linked_list.h"

void 
print_linked_list(linked_list *list)
{
  int i = 0;
  while((list)){
    printf("Element #%d: {key:\"%s\", value: \"%s\"}\n", i, list->kv.key, list->kv.value);
    list = list->next;
    i++;
  }
}

static linked_list** 
find_key(linked_list **list, char *key)
{
  linked_list **current = list;
  while(!(*current && (strcmp((*current)->kv.key, key)))){
    current = &((*current)->next);
  }
  return current; 
}

int 
linked_list_get(linked_list *l, char *key, char **value)
{
  linked_list **found = find_key(&l, key);
  if(*found){
    *value = (*found)->kv.value;
    return 0; // LINKED_LIST_GET_VALUE_FOUND
  }
  else{
    *value = NULL;
    return -1; // LINKED_LIST_GET_VALUE_NOT_FOUND
  }
}

int 
linked_list_put(linked_list **list, key_value kv)
{
  linked_list **found = find_key(list, kv.key);
  if(*found){
    (*found)->kv.value = kv.value;
    return 0; // LINKED_LIST_PUT_OK
  }
  else{
    // Just insert the new key/value at HEAD
    linked_list *tmp = *list; 
    *list = malloc(sizeof(linked_list));

    if(*list == NULL) {
      return -1; // LINKED_LIST_FAILED_ALLOCATION
    }
    else {
      (*list)->kv = kv;
      (*list)->next = tmp;
      return 0;
    }
  } 
}

int linked_list_delete(linked_list **list, char *key){
  linked_list **found = find_key(list, key);
  linked_list *cleaner;
  if (*found) {
    cleaner = *found;
    *found = (*found)->next;
    free(cleaner);
  }
  return 0;
}
