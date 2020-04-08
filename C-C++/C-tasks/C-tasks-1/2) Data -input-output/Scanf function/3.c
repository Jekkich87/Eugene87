#include <stdio.h>
int main(void){
  int dollars;
  double kurs, rub;
  scanf("%d\n", &dollars);
  scanf("%lf\n", &kurs);
  rub = dollars*kurs;
  printf("%16.13f\n", rub);
  return 0;
}
