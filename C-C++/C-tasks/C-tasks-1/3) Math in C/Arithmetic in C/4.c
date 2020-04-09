#include <stdio.h>

int main() {
	
	int grad, str_angl;
	
    double rad, pi;
    
    str_angl=180;
    
    pi = 3.1415926;
    
    scanf("%d",&grad);
    
    rad = (grad*pi)/str_angl;
    
    printf("%3.2f\n", rad);

  	return 0;
}
