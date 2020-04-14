#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    srand(time(NULL));

    int rand_digit = 0+rand()%3;

    printf("%d\n",rand_digit);
    
    return 0;
}