#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){
 int var1 = 0;
 float var2 = 0;
 double var3 = 0;
 var1 = INT_MAX;
 var2 = FLT_MAX;
 var3 = DBL_MAX;
 printf("integer max value = %d with size %lu bits\n",var1,sizeof(int)*8);
 printf("float   max value = %f with size %lu bits\n",var2,sizeof(float)*8);
 printf("double  max value = %lf with size %lu bits\n",var3, sizeof(double)*8);
 return 0;
}
