#include <stdio.h>

int main() {

    double M, N, k;

    int n, m;

    scanf("%d %d", &M, &N);

    k=M/N;

    n=((int)(k*10))%10;

    int m_o=k+10;

    m=m_o%10;

    printf("%d %d\n",m,n);
    
    return 0;
    
}