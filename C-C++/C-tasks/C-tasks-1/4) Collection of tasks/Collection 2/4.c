#include <stdio.h>
#include <math.h>

int main() {

    int x1,x2,x3,x4,x5, res;

    scanf("%d %d %d %d %d", &x1, &x2, &x3, &x4, &x5);

    res=pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2)+pow(x5,2);

    printf("%d", res);
    
    return 0;
    
}