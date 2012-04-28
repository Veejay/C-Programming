#include <stdio.h>
#include <stdlib.h>

#define LL_KEY_NOT_FOUND 99;
#define LL_DELETE_OK 0;

typedef struct key_value{
  char *key;
  char *value;
} key_value;

typedef struct linked_list {
  key_value kv; 
  struct linked_list *next;
} linked_list;


void print_linked_list(linked_list *list)
{
  int i = 0;
  while((list)){
    printf("Element #%d: {key:\"%s\", value: \"%s\"}\n", i, list->kv.key, list->kv.value);
    list = list->next;
    i++;
  }
}

int has_key(linked_list *list, char *key)
{
  return list && (strcmp(list->kv.key, key) == 0);
}

int key_position(linked_list *list, char *key)
{
  int position = -1;
  int i = 1;
  while(list){
    if(has_key(list, key)){
      return position + i;
    }
    else{
      i++;
      list = list->next;
    }
  }
  return position;
}

// GET
key_value linked_list_get(linked_list *l, char *key)
{
  while(strcmp(l->kv.key, key) != 0){
    l = l->next;
  }
  return l->kv;
}

// PUT
int linked_list_put(linked_list **list, key_value kv)
{
  linked_list *head = *list;
  // FIXME: Find something better for that -1... maybe KEY_NOT_IN_LIST
  int position = key_position(*list, kv.key);
  if(position == -1){
    linked_list *tmp = *list; 
    *list = malloc(sizeof(linked_list));
    (*list)->kv = kv;
    (*list)->next = tmp;
    return 0;
  }
  else{
    // We know where the key/value pair is, fast-forward
    int i;
    for(i = 0; i < position; i++){
      *list = (*list)->next;
    }
    // We're at the right position, update
    (*list)->kv.value = kv.value;
    *list = head;
    return 0;
  } 
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
