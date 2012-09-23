#include "hash_table.h"

int main()
{

  key_value kv1 = {.key="Bertrand", .value="Chardon"};
  key_value kv2 = {.key="Guillaume", .value="Leconte"};
  key_value kv3 = {.key="Kim", .value="Nguyen"};
  key_value kv4 = {.key="Sylvain", .value="Lebresne"};
  key_value kv5 = {.key="Ignacy", .value="Gawędzki"};
  key_value kv6 = {.key="Cédric", .value="Miachon"};
  key_value kv7 = {.key="Guillaume", .value="Miachonskyevich"};
  
  linked_list *l = NULL;

  linked_list_put(&l, kv1);
  linked_list_put(&l, kv7);
  linked_list_put(&l, kv4);
  linked_list_put(&l, kv6);
  linked_list_put(&l, kv5);
  linked_list_put(&l, kv2);
  linked_list_put(&l, kv3);

  print_linked_list(l);
  linked_list **elem = find_key(&l, "Bertrand");

  (*elem)->kv.value = "FOOBAR"; 


  print_linked_list(l);
  char *result = NULL;

  linked_list_get(l, "Bertrand", &result);

  printf("Valeur pour la clé \"Bertrand\" est %s\n", result);
  
  hashtable *h = NULL;
  printf("VALEUR DE h QUI EST UN POINTEUR DE HASHTABLE DANS MAIN: %p\n", (void*)&h);
  new_hash_table(8, &h);
  put(h, kv1);
  /* put(h, kv2); */
  /* put(h, kv3); */
  /* put(h, kv4); */
  /* put(h, kv5); */
  /* put(h, kv6); */
  /* put(h, kv7); */

  /* int status = get(h, "Bertrand", &result); */
  /* printf("VALEUR ASSOCIEE A LA CLE BERTRAND DANS LA HASH TABLE: %s\n", result); */
  return 0;
}
