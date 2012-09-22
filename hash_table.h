#include "linked_list.h"

/* typedef enum { */
/*   HASH_ALLOC_SUCCESS = 0, */
/*   HASH_ALLOC_FAILURE = -1 */
/* } hash_table_alloc_status */

typedef struct hashtable {
  int size;
  linked_list **table;
} hashtable;

hashtable*
new_hash_table(int num_buckets);

unsigned int 
hash(char *key, int size);

int 
put(hashtable *ht, key_value kv);

int
get(hashtable *ht, char *key, char **result);

int 
destroy(hashtable *ht, char *key);
