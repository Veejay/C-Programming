#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct key_value{
  char *key;
  char *value;
} key_value;

typedef enum linked_list_status_codes {
  LL_ENOMEM = -1,
  LL_PUT_OK = 0, 
  LL_VALUE_FOUND = 0,
  LL_VALUE_NOT_FOUND = -1,
  LL_DELETE_OK = 0
} ll_status_code;

typedef struct linked_list {
  key_value kv; 
  struct linked_list *next;
} linked_list;

void 
print_linked_list(linked_list *list);

linked_list** 
find_key(linked_list **list, char *key);

ll_status_code
linked_list_get(linked_list *l, char *key, char **value);

ll_status_code
linked_list_put(linked_list **list, key_value kv);

ll_status_code
linked_list_delete(linked_list **l, char *key);
