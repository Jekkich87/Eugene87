#include <stdio.h>

int main() {

    int k, n, k_m ,s, res;

    scanf("%d", &k);

    k_m=abs(k);

    n=(k_m+1)%2;

    s=k_m%2;

    res=n-s;

    printf("%d", res);


    return 0;

}