#include <stdio.h>
#include <math.h>

int main() {
	
    double a,b,y, rad_y, dgr_y, pi, res;
    
    pi = 3.141593;
    
    scanf("%lf %lf %lf", &a, &b, &y);
    
    rad_y=(y/180)*pi;
    
    dgr_y=sin(rad_y);
    
    res=(a*b*dgr_y)/2;
    
    printf("%.2lf", res);
    
  	return 0;
}
