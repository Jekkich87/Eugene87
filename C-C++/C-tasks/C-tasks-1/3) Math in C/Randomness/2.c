#include <stdio.h>

int main() {

    int N, res;

    scanf("%d",&N);

    res=rand()%(N-1);

    printf("%d\n", res);


  return 0;

}