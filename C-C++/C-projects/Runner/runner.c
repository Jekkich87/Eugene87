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

}TObject;                                                                                    // coords of player;
TObject mario;


void initMap(void);
void showMap(void);

void setObjPos(TObject *obj,float xPos, float yPos);                                        // setting position for player;
void putObjOnMap(TObject obj);                                                              // placing player on map
void initObj(TObject *obj, float xPos, float yPos, float oWidth, float oHeight);            // adding vidth and height for player char

int main(void){

    system("cls");

    initObj(&mario,39,10,3,3);

    initMap();

    putObjOnMap(mario);

    showMap();

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
        printf("%s\n",mapField[j]);
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
            mapField[j][i]='@';
        }
    }
    

}

void initObj(TObject *obj, float xPos, float yPos, float oWidth, float oHeight){

    setObjPos(obj, xPos,yPos);
    (*obj).objWidth=oWidth;
    (*obj).objHeight=oHeight;

}

