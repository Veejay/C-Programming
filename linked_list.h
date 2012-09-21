#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_linked_list(linked_list *list);

int has_key(linked_list *list, char *key);

int key_position(linked_list *list, char *key);

int linked_list_get(linked_list *l, char *key, char **value);

int linked_list_put(linked_list **list, key_value kv);

/* int linked_list_delete(linked_list **l, char *key); */
