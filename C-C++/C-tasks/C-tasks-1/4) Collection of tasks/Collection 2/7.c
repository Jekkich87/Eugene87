#include <stdio.h>

int main() {

    int k, a,b,c, res;

    scanf("%d", &k);

    a=k/100;

    b=(k%100)/10;

    c=k%10;

    res=(c*100)+(a*10)+b;

    printf("%d\n", res);

    return 0;
    
}