#include <stdio.h>

int main() {

    int K, res;

    double hundr,ten, one;

    scanf("%d", &K);

    hundr=K/100;

    one=K%10;

    ten=(K%100)-one;

    int hundr_N, ten_N, one_N;

    hundr_N=(int)one*100;

    ten_N=(int)ten;

    one_N=(int)hundr;

    res=hundr_N+ten_N+one_N;

    printf("%d\n", res);
  
    return 0;

}