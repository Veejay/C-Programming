typedef struct hashtable {
  int size;
  linked_list *table[];
} hashtable;


int hash(char *key, int size);

int put(hashtable *ht, key_value kv);

key_value get(hashtable *ht, char *key);

int destroy(hashtable *ht, char *key);
