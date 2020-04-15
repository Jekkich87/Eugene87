#include <stdio.h>
#include <math.h>

int main() {
    int x1,x2,x3,x4,x5, res, x1m,x2m,x3m,x4m,x5m;

    int a,a1,b,b1,c,c1,d,d1,e,e1;

    int ar,br,cr,dr,er;

    scanf("%d %d %d %d %d", &x1, &x2, &x3, &x4, &x5);

    x1m=fabs(x1);
    x2m=fabs(x2);
    x3m=fabs(x3);
    x4m=fabs(x4);
    x5m=fabs(x5);

    a=x1m%2; 
    b=x2m%2; 
    c=x3m%2; 
    d=x4m%2; 
    e=x5m%2;  

    a1=(x1m+1)%2; 
    b1=(x2m+1)%2; 
    c1=(x3m+1)%2; 
    d1=(x4m+1)%2; 
    e1=(x5m+1)%2;

    ar=a1-a; 
    br=b1-b; 
    cr=c1-c; 
    dr=d1-d; 
    er=e1-e;

    res=(ar+br+cr+er+dr)*-1;
    
    printf("%d", res);
  
    return 0;
    
}