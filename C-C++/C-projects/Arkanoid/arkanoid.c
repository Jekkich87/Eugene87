/*              COMMENTS and DESCRIPTIONS FOR ELEMENTS:

*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>
#include<math.h>

#define width 65                    // dimensions of gamefield
#define height 25                   // dimensions of gamefield

char field[height][width+1];        // defining gamefield

typedef struct{

    int x,y;                        // position
    int trWidth;                    // racket width

} TRacket;                          // defining t-racket
TRacket racket;

typedef struct{

    float x,y;                      // coords of ball;
    int ix,iy;                      // int coords of ball(counted form float coords)
    float alfa;                     // angle for balls`s direction
    float speed;                    // ball`s speed

}TBall;                             // defining tennis ball
TBall ball;



void initField(void);               // init gamefiled
void showField(void);               // disp gamefield

void initRacket(void);              // init t-racket
void putRacket(void);               // placing t-racket on the field
void moveRacket(int x);             // function to move racket; x - initiate left corner of racket

void initBall();                    // initiating t-ball
void putBall();                     // placint t-ball on the field                   
void moveBall(float x, float y);    // function to move ball
void autoMoveBall(void);            // claculate new position of ball, depending on ball`s direction and speed

void setCursor(int x,int y);        // setting cursor position;
void hideCursor(void);              // hiding cusor.

int main(void) {

    BOOL runBall=FALSE;             // starts ball`s movement

    //char ctrl;
    system("cls");
    hideCursor();

    initRacket();
    initBall();

    do{

        setCursor(0,0);

        if(runBall){
            autoMoveBall();
        }      
        
        initField();
        putRacket();
        putBall();

        showField();

        //ctrl=getch();

        if(GetKeyState(VK_LEFT)<0){
            moveRacket(racket.x-1);
        }
        if(GetKeyState(VK_RIGHT)<0){
            moveRacket(racket.x+1);
        }

        if(GetKeyState('W')<0){
            runBall=TRUE;
        }

        if(!runBall){
            moveBall(racket.x+racket.trWidth/2,racket.y-1);
        }
        

        Sleep(10);

    }while(GetKeyState(VK_ESCAPE)>=0);

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

void moveRacket(int x){

    racket.x=x;

    if(racket.x<1){     // checking if racket run out from borders
        racket.x=1;
    }

    if(racket.x+racket.trWidth>=width){
        racket.x=width-1-racket.trWidth;    // checking if racket run out from borders
    }

}

void setCursor(int x,int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    Sleep(10);

}

void hideCursor(void){

    CONSOLE_CURSOR_INFO CCI;
    CCI.bVisible=false;
    CCI.dwSize=1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CCI);

}

void initBall(){

    // ball.x=2;
    // ball.y=2;

    moveBall(2,2);

    ball.alfa=-1;
    ball.speed=0.5;

}

void putBall(){

    field[ball.iy][ball.ix]='*';

}

void moveBall(float x, float y){

    ball.x=x;
    ball.y=y;
    ball.ix=(int)round(ball.x);
    ball.iy=(int)round(ball.y);

}

void autoMoveBall(void){

    moveBall(ball.x+cos(ball.alfa)*ball.speed,
             ball.y+sin(ball.alfa)*ball.speed);

}
