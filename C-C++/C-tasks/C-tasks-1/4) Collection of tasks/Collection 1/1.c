#include <stdio.h>

int main() {

    int x, S_x, S_cube, V_cube;

    scanf("%d", &x);

    S_x= pow(x,2);

    S_cube=6*pow(x,2);

    V_cube=pow(x,3);

    printf("%d %d %d\n", S_x, S_cube, V_cube);
  
    return 0;
    
}