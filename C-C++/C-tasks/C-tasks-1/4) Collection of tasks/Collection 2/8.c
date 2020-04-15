#include <stdio.h>

int main() {

    int k, a, b, c, res;

    scanf("%d", &k);

    a=k/100;

    b=(k%100)/10;

    c=k%10;

    res=(b*100)+(c*10)+a;

    printf("%d\n", res);

    return 0;
    
}