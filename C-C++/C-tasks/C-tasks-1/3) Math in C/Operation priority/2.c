#include <stdio.h>
#include <math.h>

int main(void){

  float res;

  float a, b, c, d, e, f ,h; 

  scanf("%f %f %f %f %f %f %f",&a,&b,&c,&d,&e,&f,&h);

  res = a/(b*(c/(d*(e/(f*h)))));  
  
  printf("%.2f", res);

  return 0;
}