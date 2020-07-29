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
int scoreCount=0;
int maxLvl;

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
                     float oWidth, float oHeight,char inType);  // adding vidth and height for player char
void vertMoveObj(TObject *obj);                                 // vertical movement of char

BOOL isPosInMap(int x,int y);                                   // cheking, is position of cha ron map or not
BOOL isCollision(TObject o1,TObject o2);                        // checking for collision between 2 objects 

void horizonMoveMap(float dx);                                  // horizontal movement for map. char can now walk along the map/
void createLevel(int lvl);

void horizonMoveObj(TObject *obj);                              // horizontal speed for enemie
void marioCollision();                                          // chekign for collision between mario and other objects.
void deleteMoving(int i);                                       // deleting enemie if if was defeated(if mario jumps onto enemie from above)

TObject *GetNewBrick();                                         // automated creation new brick element
TObject *GetNewMoving();                                        // automated creation new enemy element

void playerDead();                                              // if mario dead - color red adn level restarting;
void putScoreOnMap();                                           // displaying score count.

void setCursor(int x,int y);
void hideCursor(void);

int main(void){


    system("mode 80,25");
    system("mode con cols=80 lines=25");
    
    setCursor(0,0);
    hideCursor();

    system("cls");

    createLevel(lvl);

    do{

        
        initMap();

        vertMoveObj(&mario);
        marioCollision();

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
            playerDead(); 
        }

        for(int i=0;i<movingLength;i++){
           
            vertMoveObj(moving+i);                                                      // addint ot enemie vertical speed. Now it can fall;
            horizonMoveObj(moving+i);
            if(moving[i].y>mapHeight){
               
                deleteMoving(i);
                i--;
                continue;
            
            
            }

            putObjOnMap(moving[i]);                                                     // placing enemie on the map
        }
        putScoreOnMap();
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
            if(obj[0].vertSpeed>0){
                (*obj).isFly=FALSE;
            }

            if((brick[i].cType=='?')&&(obj[0].vertSpeed<0)&&(obj==&mario)){                     // bricks with score now can drop score
                brick[i].cType='-';
                initObj(GetNewMoving(),brick[i].x,brick[i].y-3,3,2,'$');
                moving[movingLength-1].vertSpeed=-0.7;                                         //  score will jump out from score block
            }

            (*obj).y-=(*obj).vertSpeed;
            (*obj).vertSpeed=0;

            if(brick[i].cType=='+'){
                lvl++;
                if(lvl>maxLvl){
                    lvl=1;
                }

                system("color 2F");
                Sleep(500);

                createLevel(lvl);
                
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
    scoreCount=0;
    system("color 9F");

    brickLength=0;
    brick=realloc(brick,0);
    movingLength=0;
    moving=realloc(moving,0);

    initObj(&mario,39,10,3,3,'@');

    if(lvl==1){

        initObj(GetNewBrick(),20,20,40,5,'#');
            initObj(GetNewBrick(),30,10,5,3,'?');                                      // bricks with score
            initObj(GetNewBrick(),50,10,5,3,'?');
        initObj(GetNewBrick(),60,15,40,10,'#');
            initObj(GetNewBrick(),60,5,10,3,'-');                                      
            initObj(GetNewBrick(),70,5,5,3,'?');
            initObj(GetNewBrick(),75,5,5,3,'-');                                      
            initObj(GetNewBrick(),80,5,5,3,'?');
            initObj(GetNewBrick(),85,5,10,3,'?');
        initObj(GetNewBrick(),100,20,20,5,'#');
        initObj(GetNewBrick(),120,15,10,10,'#');
        initObj(GetNewBrick(),150,20,40,5,'#');
        initObj(GetNewBrick(),210,15,10,10,'+');

        initObj(GetNewMoving(),25,10,3,2,'o');
        initObj(GetNewMoving(),80,10,3,2,'o');                              

    }

    if(lvl==2){
     
        //brick=realloc(brick,sizeof(*brick)*brickLength);
        initObj(GetNewBrick(),20,20,40,5,'#');
        initObj(GetNewBrick(),60,15,10,10,'#');
        initObj(GetNewBrick(),80,20,20,5,'#');
        initObj(GetNewBrick(),120,15,10,10,'#');
        initObj(GetNewBrick(),150,20,40,5,'#');
        initObj(GetNewBrick(),185,15,10,10,'+');                                   // brick for ending level
    
        //moving=realloc(moving,sizeof(*moving)*movingLength);
        initObj(GetNewMoving(),25,10,3,2,'o');
        initObj(GetNewMoving(),80,10,3,2,'o');
        initObj(GetNewMoving(),120,10,3,2,'o');
        initObj(GetNewMoving(),120,10,3,2,'o');
        initObj(GetNewMoving(),165,10,3,2,'o');
        initObj(GetNewMoving(),175,10,3,2,'o');
    }

    if(lvl==3){
   
        //brick=realloc(brick,brickLength);
        initObj(GetNewBrick(),20,20,40,5,'#');
        initObj(GetNewBrick(),80,15,15,10,'#');
        initObj(GetNewBrick(),120,20,20,5,'#');
        initObj(GetNewBrick(),160,20,20,7,'+');
  
        //moving=realloc(moving,sizeof(*moving)*movingLength);
        initObj(GetNewMoving(),25,10,3,2,'o');
        initObj(GetNewMoving(),50,10,3,2,'o');
        initObj(GetNewMoving(),80,10,3,2,'o');
        initObj(GetNewMoving(),120,10,3,2,'o');
        initObj(GetNewMoving(),130,10,3,2,'o');
    }

    maxLvl=3;
    
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

    if(obj[0].cType=='o'){                                                          // if object is enemie, he will not fall from mrick. adn if score - yes;

        TObject tmp=*obj;
        vertMoveObj(&tmp);

        if(tmp.isFly==true){                                                       // checking for enemie fall. if yes - undo movement and going back 
            obj[0].x-=obj[0].horizontalSpeed;
            obj[0].horizontalSpeed=-obj[0].horizontalSpeed;
        }

    }

}

void marioCollision(){

    for(int i=0;i<movingLength;i++){

        if(isCollision(mario,moving[i])){

            if(moving[i].cType=='o'){

                    if( (mario.isFly==TRUE) && (mario.vertSpeed>0) 
                     && (mario.y+mario.objHeight<moving[i].y+moving[i].objHeight*0.5)){  //if mario jumps onto enemie from above
                        scoreCount+=50;
                        deleteMoving(i);
                        i--;
                        continue;
                        
                    }

                else{
                    playerDead();
                }

            }

            if(moving[i].cType='$'){
                scoreCount+=100;
                deleteMoving(i);
                i--;
                continue;
            }

        }

        
    }

}

void deleteMoving(int i){
    
    movingLength--;
    moving[i]=moving[movingLength];
    moving=realloc(moving,sizeof(*moving)*movingLength);

}

TObject *GetNewBrick(){

    brickLength++;
    brick=realloc(brick,sizeof(*brick)*brickLength);
    return brick+brickLength-1;

}

TObject *GetNewMoving(){

    movingLength++;
    moving=realloc(moving,sizeof(*moving)*movingLength);
    return moving+movingLength-1;

}


void playerDead(){

    system("color 4f");
    Sleep(500);
    createLevel(lvl);

}

void putScoreOnMap(){
    char c[30];
    sprintf(c,"Score: %d ",scoreCount);
    int len=strlen(c);
    for(int i=0;i<len;i++){
        mapField[1][i+5]=c[i];
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

