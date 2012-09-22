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

  linked_list_put(&l, kv4);
  linked_list_put(&l, kv5);
  linked_list_put(&l, kv6);
  linked_list_put(&l, kv2);
  linked_list_put(&l, kv3);
  linked_list_put(&l, kv7);

  char *result;

  linked_list_get(l, "Bertrand", &result);

  printf("La valeur récupérée dans la liste chainée pour la clé Bertrand est %s\n", result);

  print_linked_list(l);

  hashtable* h = new_hash_table(8);
  put(h, kv1);
  put(h, kv2);
  put(h, kv3);
  put(h, kv4);
  put(h, kv5);
  put(h, kv6);
  put(h, kv7);

  key_value kv;
  result = get(h, "Bertrand", &result);
  printf("La valeur récupérée pour la clé Bertrand est %s\n", result);
  
  result = get(h, "Guillaume", &result);
  printf("La valeur récupérée pour la clé Guillaume est %s\n", result);

  result = get(h, "ImaginaryKey", &result);
  printf("La valeur récupérée pour la clé ImaginaryKey est %s\n", result);
  

  /* printf("DELETING ELEMENT WITH KEY foobar\n"); */
  /* linked_list_delete(&l, "foobar"); */
  
  /* printf("DELETING ELEMENT WITH KEY moobar\n"); */
  /* linked_list_delete(&l, "moobar"); */

  /* printf("We just deleted two values that didn't exist in the list\n"); */
  /* printf("\n=========================\n"); */
  /* print_linked_list(l); */
  
  /* printf("\n=========================\n"); */
  /* printf("DELETING ELEMENT WITH KEY Kim\n"); */
  /* linked_list_delete(&l, "Kim"); */
  /* print_linked_list(l); */

  /* printf("DELETING ELEMENT WITH KEY Bertrand\n"); */
  /* linked_list_delete(&l, "Bertrand"); */
  /* printf("\n=========================\n"); */
  /* print_linked_list(l); */
  return 0;
}
