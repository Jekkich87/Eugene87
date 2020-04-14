#include <stdio.h>

int main() {

    int h=0,s=0,m=0;

    scanf("%d", &s);

    m=(s/60)%60;

    h=(s/60)/60;

    printf("%d %d\n", h, m);
  
    return 0;
}