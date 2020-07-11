#include<stdio.h>
#include<conio.h>

#define width 65                //dimensions of gamefield
#define height 25

char field[height][width];      //defining gamefield


void initField(void);           // init gamefiled
void showField(void);           //displaying gamefield

int main(void) {
    return 0;
}

void initField(void){     
    int i=0;
    for(i=0;i<width;i++){
        field[0][i]='#';
    }
}

void showField(){       
    printf("%s",field[0]);
}