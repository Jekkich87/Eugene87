#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define mapWidth 80
#define mapHeight 25

char mapField[mapHeight][mapWidth+1];
int lvl=1;

typedef struct SObject{

    float x,y;
    float objWidth,objHeight;
    float vertSpeed;                                            // vertical speed of character
    BOOL isFly;                                                 //checking, is Mario on the air or not
    char cType;
    float horizontalSpeed;

}TObject;                                                       // coords of player;
TObject mario;
TObject *brick=NULL;
int brickLength;

TObject *moving=NULL;                                           // enemies;
int movingLength;                                               // size of enemie;

void initMap(void);
void showMap(void);

void setObjPos(TObject *obj,float xPos, float yPos);            // setting position for player;
void putObjOnMap(TObject obj);                                  // placing player on map
void initObj(TObject *obj, float xPos, float yPos, 
                     float oWidth, float oHeight,char inType);              // adding vidth and height for player char
void vertMoveObj(TObject *obj);                                 // vertical movement of char

BOOL isPosInMap(int x,int y);                                   // cheking, is position of cha ron map or not
BOOL isCollision(TObject o1,TObject o2);                        // checking for collision between 2 objects 

void horizonMoveMap(float dx);                                  // horizontal movement for map. char can now walk along the map/
void createLevel(int lvl);

void horizonMoveObj(TObject *obj);                              // horizontal speed for enemie

void setCursor(int x,int y);
void hideCursor(void);

int main(void){


    system("mode 80,25");
    system("mode con cols=80 lines=25");
    system("color 9F");
    setCursor(0,0);
    hideCursor();

    system("cls");

    createLevel(lvl);

    do{

        initMap();

        vertMoveObj(&mario);

        for(int i=0;i<brickLength;i++){
            putObjOnMap(brick[i]);
        }

        putObjOnMap(mario);

        if((mario.isFly==FALSE)&&(GetKeyState(VK_SPACE)<0)){                            // mario can jump)
            mario.vertSpeed=-1;
        }

        if(GetKeyState(VK_LEFT)<0){
            horizonMoveMap(1);
        }
        if(GetKeyState(VK_RIGHT)<0){
            horizonMoveMap(-1);
        }

        if(mario.y>mapHeight){                                                          // if mario falls out the map, level reloading;
            createLevel(lvl); 
        }

        for(int i=0;i<movingLength;i++){
            putObjOnMap(moving[i]);                                                     // placing enemie on the map
            vertMoveObj(moving+i);                                                      // addint ot enemie vertical speed. Now it can fall;
            horizonMoveObj(moving+i);
        }

        setCursor(0,0);
        
        showMap();

        Sleep(10);

    }while(GetKeyState(VK_ESCAPE)>=0);

}

void initMap(void){

    int i=0,j=0;

    for(i=0;i<mapWidth;i++){
        mapField[0][i]=' ';
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
                mapField[j][i]=obj.cType;
            }
        }
    }  

}

void initObj(TObject *obj, float xPos, float yPos, float oWidth, float oHeight,char inType){

    setObjPos(obj, xPos,yPos);
    (*obj).objWidth=oWidth;
    (*obj).objHeight=oHeight;
    (*obj).vertSpeed=0;
    (*obj).cType=inType;
    (*obj).horizontalSpeed=0.2;

}



void vertMoveObj(TObject *obj){

    (*obj).isFly=TRUE;
    (*obj).vertSpeed+=0.05;
    setObjPos(obj,(*obj).x,(*obj).y+(*obj).vertSpeed);

    for(int i=0;i<brickLength;i++){
        if(isCollision(*obj,brick[i])){
            (*obj).y-=(*obj).vertSpeed;
            (*obj).vertSpeed=0;
            (*obj).isFly=FALSE;
            if(brick[i].cType=='+'){
                lvl++;
                if(lvl>2){
                    lvl=1;
                }
                createLevel(lvl);
                Sleep(1000);
            }
            break;
        }
    }

}

BOOL isPosInMap(int x,int y){
    return((x>=0)&&(x<mapWidth)&&(y>=0)&&(y<mapHeight));
}

BOOL isCollision(TObject o1,TObject o2){
    return(((o1.x+o1.objWidth)>o2.x)&&(o1.x<(o2.x+o2.objWidth))
    &&((o1.y+o1.objHeight)>o2.y)&&(o1.y<(o2.y+o2.objHeight)));
}

void horizonMoveMap(float dx){

    mario.x-=dx;
    for(int i=0;i<brickLength;i++){
        if(isCollision(mario,brick[i])){
            mario.x+=dx;
            return;
        }       
    }

    mario.x+=dx;

    for(int i=0;i<brickLength;i++){
        brick[i].x+=dx;
    }

    for(int i=0;i<movingLength;i++){
        moving[i].x+=dx;
    }

}   

void createLevel(int lvl){

    initObj(&mario,39,10,3,3,'@');

    if(lvl==1){
        brickLength=6;
        brick=realloc(brick,brickLength);
        initObj(brick+0,20,20,40,5,'#');
        initObj(brick+1,60,15,10,10,'#');
        initObj(brick+2,80,20,20,5,'#');
        initObj(brick+3,120,15,10,10,'#');
        initObj(brick+4,160,20,15,5,'#');
        initObj(brick+5,185,20,20,7,'+');                                   //brick for ending level
        movingLength=1;
        moving=realloc(moving,sizeof(*moving)*movingLength);
        initObj(moving+0,25,10,3,2,'o');
    }

    if(lvl==2){
        brickLength=4;
        brick=realloc(brick,brickLength);
        initObj(brick+0,20,20,40,5,'#');
        initObj(brick+1,80,15,15,10,'#');
        initObj(brick+2,95,20,20,5,'#');
        initObj(brick+3,125,20,20,7,'+');   
    }
    
}

void horizonMoveObj(TObject *obj){
    obj[0].x+=obj[0].horizontalSpeed;

    for(int i=0;i<brickLength;i++){                                            // checking for collision between enemie adn brick
        if(isCollision(obj[0],brick[i])){
            obj[0].x-=obj[0].horizontalSpeed;
            obj[0].horizontalSpeed=-obj[0].horizontalSpeed;
            return;
        }
    }
    TObject tmp=*obj;
    vertMoveObj(&tmp);

    if(tmp.isFly==true){                                                       // checking for enemie fall. if yes - undo movement and going back 
        obj[0].x-=obj[0].horizontalSpeed;
        obj[0].horizontalSpeed=-obj[0].horizontalSpeed;
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

