#include <stdio.h>

int main() {

  int k, n, s, res;

  scanf("%d", &k);

  n=(k+1)%2;

  s=k%2;

  res=n-s;

  printf("%d", res);
  
  return 0;
  
}