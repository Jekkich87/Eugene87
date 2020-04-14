#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 
 
int main() {
    int r_ic, r_oc, W_rng;


    double S_ic, S_oc, S_gk, S_rnd;
    
    double pi = 3.14159265358979323846;

    scanf("%d %d", &r_ic, &r_oc);

    W_rng=r_oc-r_ic;

    S_oc=pi*pow(r_oc,2);

    S_ic=pi*pow(r_ic,2);

    S_rnd=S_oc-S_ic;

    S_gk=S_rnd*100;

    printf("%d %.2lf", W_rng, S_gk);

    return 0;
}