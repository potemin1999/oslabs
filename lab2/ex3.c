#include <stdio.h>

//   ex5: get mode
int get_mode();

//   reads and return height of figure
int get_height();

//   prints triangle
int print_triangle(int n);

//   ex5: prints triangle 2
int print_triangle2(int n);

//   ex5: prints triangle 3
int print_triangle3(int n);

//   ex5: prints rectangle
int print_rectangle(int n);

//   ex5 advanced: prints circle! (almost)
int print_circle(int d);


//   entry point
int main(){
 int mode = get_mode();
 if ( mode>5 || mode<1 )
    return 0;
 int n = get_height();
 if (n<1)
   return 0;
 int result = 0;
 switch(mode){
  case 1:{
    result = print_triangle(n);
    break;
  }
  case 2:{
    result = print_triangle2(n);
    break;
  }
  case 3:{
    result = print_triangle3(n);
    break;
  }
  case 4:{
    result = print_rectangle(n);
    break;
  }
  case 5:{
    result = print_circle(n);
    break;
  }
 }
 return result>0 ? 0 : result;
}


int get_mode(){
 printf("Write 1 to draw a triangle\n");
 printf("Write 2 to draw a left-sided triangle\n");
 printf("Write 3 to draw an another triangle\n");
 printf("Write 4 to draw the rectangle\n");
 printf("Write 5 to draw a circle (better works with big diameter)\n");
 printf("Write any other number to exit\n");
 int mode = 0;
 printf(": ");
 scanf("%d",&mode);
 return mode;
}


int get_height(){
 int height = 0;
 //  read triagle height and return it
 printf("Write desired height of figure: ");
 scanf("%d",&height);
 return height;
}


int print_triangle(int n){
 //  init buffer and its contents
 char buffer [2*n+1];
 for ( int i = 0 ; i<2*n ; buffer[i++]=' ' );
 //  draw buffer at once is better,
 //     than each symbol one by one
 buffer[2*n] = '\0';
 buffer[n] = '*';
 for (int i = 0 ; i<n ; ++i ){
  printf(" %s \n",buffer);
  //  expand triagle's sides
  if (i!=n-1){
   buffer[n-i-1] = '*';
   buffer[n+i+1] = '*';
  }
 }
 return n;
}

// ex5
int print_triangle2(int n){
 char buffer[n+1];
 for ( int i = 0 ; i<n+1 ; buffer[i++]=' ' );
 buffer[n] = '\0';
 for ( int i = 0 ; i<n ; ++i ){
  buffer[i]='*';
  printf("%s \n",buffer);
 }
 return n;
}

// ex5
int print_triangle3(int n){
 if ( n % 2 == 0 ){
  printf("Unable to print perfect left-sided triangle, rounding height to %d\n",++n);
 }
 char buffer[n+1];
 for ( int i = 0 ; i<n ; buffer[i++]=' ' );
 buffer[n] = '\0';
 for (int i = 0; i<n ; ++i){
  if ( i <= (n>>1) ){
   buffer[i] = '*';
  }else{
   buffer[n-i] = ' ';
  }
  printf("%s\n",buffer);
 }
 return n;
}

// ex5
int print_rectangle(int n){
 char buffer[n+1];
 for ( int i = 0 ; i<n+1 ; buffer[i++]='*' );
 buffer[n] = '\0';
 for ( int i = 0 ; i<n ; ++i ){
  printf("%s \n",buffer);
 }
}

// ex5
int is_circle(int x,int y,int d){
 int dx2 = d-2*x-1;
 int dy2 = d-2*y-1;
 if ( d*d > dx2*dx2 + dy2*dy2 )
     return 1;
 return 0;
}

// ex5
int print_circle(int d){
 char buffer[d+1];
 buffer[d]='\0';
 for ( int i = 0 ; i < d ; i++ ){
  for ( int j = 0 ; j < d ; j++ ){
   buffer[j] = is_circle(i,j,d) ? '*' : ' ' ;
  }
  printf("%s\n",buffer);
 }
 return d;
}
