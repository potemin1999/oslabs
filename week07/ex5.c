#include <stdio.h>

int main() {
  char **s = 0;
//char foo[] = "Hello World";
  char *foo = "Hello the world without segfaults!";
// *s = foo;
  s = &foo;

/** "s" is a pointer, not a "char*" */
//printf("s is %s\n”,s);
  printf("s is %p\n",s);

/** pointer arithmetic looks better than indexes*/
//s[0] = foo;
  s = &foo;
//printf("s[0] is %s\n",s[0]);
  printf("s[0] is %s\n",*s);
//return(0);
  return 0;
}
