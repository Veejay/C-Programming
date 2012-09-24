#include "hash_table.h"

int main()
{
  key_value kv1 = {.key="Bertrand", .value="Chardon"};
  key_value kv9 = {.key="Bertrand", .value="Bolton"};
  key_value kv2 = {.key="Guillaume", .value="Leconte"};
  key_value kv3 = {.key="Kim", .value="Nguyen"};
  key_value kv4 = {.key="Sylvain", .value="Lebresne"};
  key_value kv5 = {.key="Ignacy", .value="Gawędzki"};
  key_value kv6 = {.key="Cédric", .value="Miachon"};
  key_value kv7 = {.key="Guillaume", .value="Miachonskyevich"};
  
  linked_list *l = NULL;

  linked_list_put(&l, kv1);
  linked_list_put(&l, kv9);

  print_linked_list(l);
  char *result = NULL;

  hashtable *h = NULL;
  ht_status_code sc = new_hash_table(8, &h);
  if(sc == HT_CREATE_OK){
    printf("SUCCESSFULLY ALLOCATED MEMORY FOR HASH TABLE\n");
  }
  printf("SIZE OF HASH TABLE: %d\n", (int)h->size);
  put(h, kv1);
  int status = get(h, "Bertrand", &result);
  printf("VALEUR ASSOCIEE A LA CLE BERTRAND DANS LA HASH TABLE: %s\n", result);
  /* put(h, kv2); */
  /* put(h, kv3); */
  /* put(h, kv4); */
  /* put(h, kv5); */
  /* put(h, kv6); */
  /* put(h, kv7); */

  return 0;
}
