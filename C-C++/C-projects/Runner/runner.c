#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define mapWidth 80
#define mapHeight 25

char mapField[mapHeight][mapWidth+1];

typedef struct SObject{

    float x,y;
    float objWidth,objHeight;
    float vertSpeed;                                            // vertical speed of character

}TObject;                                                       // coords of player;
TObject mario;
TObject brick[1];

void initMap(void);
void showMap(void);

void setObjPos(TObject *obj,float xPos, float yPos);            // setting position for player;
void putObjOnMap(TObject obj);                                  // placing player on map
void initObj(TObject *obj, float xPos, float yPos, 
                     float oWidth, float oHeight);              // adding vidth and height for player char
void vertMoveObj(TObject *obj);                                 // vertical movement of char

BOOL isPosInMap(int x,int y);                                   //cheking, is position of cha ron map or not
BOOL isCollision(TObject o1,TObject o2);                        //checking for collision between 2 objects 


void setCursor(int x,int y);
void hideCursor(void);

int main(void){


    system("mode 80,25");
    system("mode con cols=80 lines=25");
    setCursor(0,0);
    hideCursor();

    system("cls");

    initObj(&mario,39,10,3,3);
    initObj(brick,20,20,40,5);

    do{

        initMap();

        vertMoveObj(&mario);
        putObjOnMap(mario);
        putObjOnMap(brick[0]);

        if(GetKeyState(VK_SPACE)<0){                            //mario can jump)
            mario.vertSpeed=-0.7;
        }

        setCursor(0,0);
        
        showMap();

        Sleep(10);

    }while(GetKeyState(VK_ESCAPE)>=0);

    
}

void initMap(void){

    int i=0,j=0;

    for(i=0;i<mapWidth;i++){
        mapField[0][i]='.';
    }

    mapField[0][mapWidth]='\0';

    for(j=1;j<mapHeight;j++){
        sprintf(mapField[j],mapField[0]);
    }
    
}

void showMap(void){

    int i=0,j=0;

    mapField[mapHeight-1][mapWidth-1]='\0';

    for(j=0;j<mapHeight;j++){
        printf("%s",mapField[j]);
    }
 
}

void setObjPos(TObject *obj,float xPos, float yPos){

    (*obj).x=xPos;
    (*obj).y=yPos;

}

void putObjOnMap(TObject obj){

    int i=0,j=0;

    int ix=(int)round(obj.x);
    int iy=(int)round(obj.y);

    int iWidth=(int)round(obj.objWidth);
    int iHeight=(int)round(obj.objHeight);

    for(i=ix;i<(ix+iWidth);i++){
        for(j=iy;j<(iy+iHeight);j++){
            if(isPosInMap(i,j)){
                mapField[j][i]='@';
            }
        }
    }  

}

void initObj(TObject *obj, float xPos, float yPos, float oWidth, float oHeight){

    setObjPos(obj, xPos,yPos);
    (*obj).objWidth=oWidth;
    (*obj).objHeight=oHeight;
    (*obj).vertSpeed=0;

}



void vertMoveObj(TObject *obj){

    (*obj).vertSpeed+=0.5;
    setObjPos(obj,(*obj).x,(*obj).y+(*obj).vertSpeed);
    if(isCollision(*obj,brick[0])){
        (*obj).y-=(*obj).vertSpeed;
        (*obj).vertSpeed=0;
    }

}

BOOL isPosInMap(int x,int y){
    return((x>=0)&&(x<mapWidth)&&(y>=0)&&(y<mapHeight));
}

BOOL isCollision(TObject o1,TObject o2){
    return(((o1.x+o1.objWidth)>o2.x)&&(o1.x<(o2.x+o2.objWidth))
    &&((o1.y+o1.objHeight)>o2.y)&&(o1.y<(o2.y+o2.objHeight)));
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

