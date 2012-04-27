#include <stdio.h>
#include <string.h>

char* reverse(char *s)
{
  int i, placeholder; 
  int l = strlen(s) - 1; 
  for(i = 0; i < (l / 2); i++){
    placeholder = *(s+i); 
    *(s+i) = *(s+l-i);
    *(s+l-i) = placeholder; 
  }
  return s;
} 

int main()
{
  char s[] = "this is a test string"; 
  printf("The reversed version of \"%s\" is ", s);
  printf("\"%s\"\n", reverse(s));
  return 0;
}
