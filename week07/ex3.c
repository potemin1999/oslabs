#include <stdio.h>
/**
 * This exercise demonstrates capabilities
 *  of the 4th task implementation.
 * Functions my_malloc, my_free and my_realloc
 *  are located in ./ex4.h, and are similar to
 *  the system ones
 */
#include "ex4.h"

int array_resize(){
  // Allows user to specify the original array size, stored in variable n1.
  printf("Enter original array size:");
  int n1=0;
  scanf("%d",&n1);
  //Create a new array of n1 ints
  int* a1 = my_malloc(n1*sizeof(int));
  int i;
  for(i=0; i<n1; i++){
    //Set each value in a1 to 100
    a1[i]=100;
    //Print each element out (to make sure things look right)
    printf("%d ",a1[i]);
  }
  //User specifies the new array size, stored in variable n2.
  printf("\nEnter new array size: ");
  int n2=0;
  scanf("%d",&n2);
  //Dynamically change the array to size n2
  a1 = my_realloc(a1,n2*sizeof(int));
  //If the new array is a larger size, set all new members to 0. Reason: dont want to use uninitialized variables.
  for (i=n1; i<n2; i++){
    a1[i] = 0;
  }
  for(i=0; i<n2;i++){
    //Print each element out (to make sure things look right)
    printf("%d ",a1[i]);
  }
  printf("\n");
  my_free(a1);
  printf("memory cleaned up, exiting\n");
  //Done with array now, done with program :D
  return 0;
}

int main(){
  array_resize();
  return 0;
}
