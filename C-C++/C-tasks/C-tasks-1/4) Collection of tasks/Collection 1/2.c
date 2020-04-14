#include <stdio.h>

int main() {

   int h, r;

    double pi=3.14159265358979323846, Vc, Vk;

    scanf("%d %d", &r, &h);

    Vc=(double)h*pi*pow(r,2);

    Vk=(double)(1.00/3.00)*h*pi*pow(r,2);

    printf("%.2lf %.2lf", Vc, Vk);
    
    return 0;
  
}