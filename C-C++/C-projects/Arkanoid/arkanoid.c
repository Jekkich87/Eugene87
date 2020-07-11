/*              COMMENTS and DESCRIPTIONS FOR ELEMENTS:

*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define width 65                    //dimensions of gamefield
#define height 25                  //dimensions of gamefield

char field[height][width+1];      //defining gamefield

typedef struct{

    int x,y; //position
    int trWidth; //racket width

} TRacket;                         //defining t-racket
TRacket racket;                    


void initField(void);            // init gamefiled
void showField(void);           // disp gamefield

void initRacket(void);         // init t-racket
void putRacket(void);         // placing t-racket on the field


int main(void) {

    initRacket();
    initField();

    putRacket();
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

    for(i=2;i<height;i++){
        strncpy(field[i],field[1],width+1);
    }


}

void showField(void){

    int i=0;

    for(i=0;i<height;i++){
        printf("%s\n",field[i]);
    }

}

void initRacket(void){

    racket.trWidth=7;
    racket.x=(width-racket.trWidth)/2;
    racket.y=height-1;

}

void putRacket(void){

    int i=0;
    for(i=racket.x;i<racket.x+racket.trWidth;i++){
        field[racket.y][i]='@';
    }

}