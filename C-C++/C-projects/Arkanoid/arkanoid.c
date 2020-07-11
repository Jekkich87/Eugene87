#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define width 65                //dimensions of gamefield
#define height 25

char field[height][width+1];      //defining gamefield


void initField(void);           // init gamefiled
void showField(void);           // displaying gamefield


int main(void) {

    initField();
    showField();

    return 0;

}

void initField(void){

    int i=0;
    for(i=0;i<width;i++){
        field[0][i]='#';    
    }
    field[0][width]='\0';

    strncpy(field[1],field[0],width+1);
    for(i=1;i<width-1;i++){
        field[1][i]=' ';    
    }

    for(i=2;i<height-1;i++){
        strncpy(field[i],field[1],width+1);
    }


}

void showField(void){

    int i=0;

    for(i=0;i<height;i++){
        printf("%s\n",field[i]);
    }

}