#include <stdio.h>

int main() {
    int N;
    double a_t, a_s, a_d, a_e, res;
    scanf("%d", &N);
    a_t=(N/1000);
    a_s=(N%1000/100);
    a_d=(N%100)/10;
    a_e=(N%100)%10;
    //int an_t=a_t;
    //int an_s=a_s;
    //int an_d=a_d;
    //int an_e=a_e;
    //int a_ch=an_t*an_d;
    //int a_nch=an_s*an_e;
    //res=a_ch/a_nch;
    res=(a_t*a_d)/(a_s*a_e);
    printf("%.2lf\n", res);
  // put your code here
  return 0;
}