#include <stdio.h>

int main() {

    double e1,e2,e3;

    int n1,n2,n3,n4,n5;
    
    n1=1/1;
    n2=(2/1)*(2-1);
    n3=(3/1)*(3/3)*(3-1);
    n4=(4/1)*(4%3)*(4-1)*(4/2);
    n5=(5/1)*(5-1)*(5-2)*(5%3)*(5%4);
    
    e1=(float)1+((float)1)/n1+((float)1)/n2+((float)1)/n3;
    e2=(float)1+((float)1)/n1+((float)1)/n2+((float)1)/n3+((float)1)/n4;
    e3=(float)1+((float)1)/n1+((float)1)/n2+((float)1)/n3+((float)1)/n4+((float)1)/n5;

    printf("%.5lf\n%.5lf\n%.5lf\n", e1,e2,e3);

    return 0;

}