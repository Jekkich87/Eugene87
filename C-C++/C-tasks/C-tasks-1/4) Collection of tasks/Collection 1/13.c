#include <stdio.h>

int main() {
    
    int n1,n2,n3,n4,n5;

	double x, ex_1, ex_2;

	scanf("%lf", &x);

	n1=1/1;
    n2=(2/1)*(2-1);
    n3=(3/1)*(3/3)*(3-1);
    n4=(4/1)*(4%3)*(4-1)*(4/2);
    n5=(5/1)*(5-1)*(5-2)*(5%3)*(5%4);

	ex_1=exp(x);
	ex_2=(float)1+x/n1+(pow(x,2))/n2+(pow(x,3))/n3+(pow(x,4))/n4+(pow(x,5))/n5;

	printf("%.6lf\n%.6lf\n", ex_1, ex_2);
 
    return 0;

}