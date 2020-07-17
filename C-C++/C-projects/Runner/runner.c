#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define mapWidth 80
#define mapHeight 25

char mapField[mapHeight][mapWidth+1];

void initMap(void);
void showMap(void);

int main(void){

    system("cls");

    initMap();
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
        printf("%s\n",mapField[i]);
    }


    
    
}



