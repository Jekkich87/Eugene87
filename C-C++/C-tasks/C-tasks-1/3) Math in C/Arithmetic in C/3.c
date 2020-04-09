#include <stdio.h>

int main() {
	
	int start_m, end_m, dif;

    double tariff, pay;
    
    scanf("%d %d %lf", &start_m, &end_m, &tariff);
    
    dif= end_m-start_m;
    
    pay=(float)dif*tariff;
    
    printf("%4.2f", pay);

  	return 0;
}
