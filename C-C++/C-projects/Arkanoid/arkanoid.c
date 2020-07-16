/*              COMMENTS and DESCRIPTIONS FOR ELEMENTS:

*/
#define _USE_MATH_DEFINES
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
int hitCount=0;                     // hit counter
int maxHitCount=0;                  // max hit counter


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
TBall ballPos;                      // ball position


void initField(int level);               // init gamefiled; added level swithcer and inititation
void showField(int level);               // disp gamefield; 

void initRacket(void);              // init t-racket
void putRacket(void);               // placing t-racket on the field
void moveRacket(int x);             // function to move racket; x - initiate left corner of racket

void initBall();                    // initiating t-ball
void putBall();                     // placint t-ball on the field                   
void moveBall(float x, float y);    // function to move ball
void autoMoveBall(void);            // claculate new position of ball, depending on ball`s direction and speed

void showInstructions(void);        // game instructions

void showPrewiev(int level);        // level prewiev

void setCursor(int x,int y);        // setting cursor position;
void hideCursor(void);              // hiding cusor.

int main(void) {

    int level=0;                    // level
    BOOL runBall=FALSE;             // starts ball`s movement
    showInstructions();
    //char ctrl;
    system("cls");
    hideCursor();

    initRacket();
    initBall();

    showPrewiev(level);

    do{

        setCursor(0,0);

        if(runBall){
            autoMoveBall();
        }

        if(ball.iy>=height){        // cheking if ball run out from field

            runBall=FALSE;

            if(hitCount>maxHitCount){
                maxHitCount=hitCount;
            }

            hitCount=0;

        }

        if(hitCount==6){

            level++;
            runBall=FALSE;
            hitCount=0;
            maxHitCount=0;
            showPrewiev(level);

        }      
        
        initField(level);

        putRacket();
        putBall();

        showField(level);

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

void initField(int level){

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

    if(level==1){
        for(i=15;i<30;i++){
            field[3][i]='#';
        }
    }

    if(level==2){
        for(i=30;i<57;i++){
            field[10][i]='#';
        }

        for(i=2;i<19;i++){
            field[18][i]='#';
        }
    }

}

void showField(int level){

    int i=0;

    for(i=0;i<height;i++){

        printf("%s",field[i]);

        if(i==4){
            printf("   Current level:  %d   ", level);
        }

        if(i==5){
            printf("   Hit counter:  %d   ", hitCount);
        }

        if(i==6){
            printf("   Max hint count:  %d", maxHitCount);
        }

        if(i<height-1){
            printf("\n");
        }

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

    if(racket.x<1){                         // checking if racket run out from borders
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
    //Sleep(10);

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

    if(ball.alfa<0){
        ball.alfa+=M_PI*2;
    }

    if(ball.alfa>M_PI*2){
        ball.alfa-=M_PI*2;
    }

    ballPos=ball;

    moveBall(ball.x+cos(ball.alfa)*ball.speed,
             ball.y+sin(ball.alfa)*ball.speed);

    if((field[ball.iy][ball.ix]=='#')||(field[ball.iy][ball.ix]=='@')){

        if(field[ball.iy][ball.ix]=='@'){
            hitCount++;
        }

        if((ball.ix!=ballPos.ix)&&(ball.iy!=ballPos.iy)){

            if(field[ballPos.iy][ballPos.ix]==field[ball.iy][ballPos.ix]){
                ballPos.alfa=ballPos.alfa+M_PI;
            }

            else{

                if(field[ballPos.iy][ballPos.ix]=='#'){
                    ballPos.alfa=(2*M_PI-ballPos.alfa)+M_PI;
                }

                else{
                    ballPos.alfa=(2*M_PI-ballPos.alfa);
                }

            }

        }

        else if(ball.iy==ballPos.iy){
            ballPos.alfa=(2*M_PI-ballPos.alfa)+M_PI;
        }

        else{
            ballPos.alfa=(2*M_PI-ballPos.alfa);
        }

        ball=ballPos;

        autoMoveBall();

    }

}

void showPrewiev(int level){

    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t LEVEL:  %d",level);
    Sleep(1000);
    system("cls");

}

void showInstructions(void){

    system("cls");
    printf("\n\n\n\n \t\t\t\t This is arkanoid.\n");
    printf("\n\n \t\t\t\t You must hit ball by tennis racket.\n");
    printf("\n\n \t\t\t\t To start the game press \"W\"-button.\n");
    printf("\n\n \t\t\t\t To move racket to the left - press \"Left arrow\"-button.\n");
    printf("\n\n \t\t\t\t To move racket to the right - press \"Right arrow\"-button.\n");
    printf("\n\n \t\t\t\t If you hit ball 6 times, you will switch to the next level.\n");
    printf("\n\n \t\t\t\t To leave the game press \"ESC\"-button\n");
    printf("\n\n \t\t\t\t GOOD LUCK!!!\n");
    Sleep(10000);
    system("cls");
}