#include "hashtable.h"

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

  print_linked_list(l);
  printf("Position de Sylvain Lebresne dans la liste: %d\n", key_position(l, "Bertrand"));

  printf("=========================\n");
  printf("VALUE FOR KEY Bertrand: %s\n", linked_list_get(l, "Bertrand").value);
  printf("=========================\n");

  printf("DELETING ELEMENT WITH KEY foobar\n");
  linked_list_delete(&l, "foobar");
  
  printf("DELETING ELEMENT WITH KEY moobar\n");
  linked_list_delete(&l, "moobar");

  printf("We just deleted two values that didn't exist in the list\n");
  printf("\n=========================\n");
  print_linked_list(l);
  
  printf("\n=========================\n");
  printf("DELETING ELEMENT WITH KEY Kim\n");
  linked_list_delete(&l, "Kim");
  print_linked_list(l);

  printf("DELETING ELEMENT WITH KEY Bertrand\n");
  linked_list_delete(&l, "Bertrand");
  printf("\n=========================\n");
  print_linked_list(l);
  return 0;
}