#include "linked_list.h"

typedef enum hash_table_status_codes {
  HT_ENOMEM = -1,
  HT_PUT_OK = 0,
  HT_CREATE_OK = 0,
  HT_DELETE_OK = 0,
  HT_VALUE_FOUND = 0,
  HT_VALUE_NOT_FOUND = -1,
  HT_UNKNOWN_ERROR = -2
} ht_status_code; 

typedef struct hashtable {
  int size;
  linked_list **table;
} hashtable;

ht_status_code
new_hash_table(int num_buckets, hashtable **ht);

ht_status_code 
put(hashtable *ht, key_value kv);

ht_status_code
get(hashtable *ht, char *key, char **result);

ht_status_code
destroy(hashtable *ht, char *key);
