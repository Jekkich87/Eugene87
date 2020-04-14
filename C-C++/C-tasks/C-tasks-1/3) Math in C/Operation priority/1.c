#include <stdio.h>
#include <math.h>

int main() {
   double a, b, c, p, S, p_a, p_b, p_c;

   scanf("%lf %lf %lf", &a, &b, &c);

   p=(a+b+c)/2;

   p_a=p-a;

   p_b=p-b;

   p_c=p-c;

   S=sqrt(p*p_a*p_b*p_c);
   
   printf("%.2lf\n", S);
  
  return 0;
}