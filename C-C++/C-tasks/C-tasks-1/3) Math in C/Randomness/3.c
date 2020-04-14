#include <stdio.h>

int main() {

    int S, E, res;

    scanf("%d %d",&S, &E);

    res=E-rand()%(E-S);

    printf("%d\n", res);

    return 0;
    
}