#include <stdio.h>
#include <math.h>

int main() {

    int N; 

    long int K, dv_g, dd_g, res;

    dv_g=pow(2,30);

    dd_g=pow(10,9);

    scanf("%d", &N);

    res=(dv_g-dd_g)*N;

    printf("%ld\n", res);
    
    return 0;
}