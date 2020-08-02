#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>
#include<math.h>

#define width 80
#define height 25

struct{
    char map[height][width+1];
}loc;

struct{
    POINT pos;
}player;

char map[height][width+1];

void loc_LoadFormFile(char* filename);              // function to loading location from file
void showMap(void);                                 // function for displaying map
void loc_putOnMap(void);

void initPlayer(int x, int y);
void player_putOnMap(void);


int main(void) {

    system("cls");
    system("mode 80,25");
    system("mode con cols=80 lines=25");

    loc_LoadFormFile("map_0_0.txt");
    loc_putOnMap();

    initPlayer(5,5);
    player_putOnMap();
    
    showMap();


    return 0;
}

void loc_LoadFormFile(char* filename){

    //memset(&loc.map,' ',sizeof(loc));            // filling in the map by space char;
    for(int i=0;i<height;i++){
        loc.map[i][width]='\0';
    }
    FILE* f=fopen(filename,"r");
    char c[80];
    int line=0;
    while(!feof(f)){
        fgets(c,width,f);
        int cnt=strlen(c);
        if(c[cnt]=='\n'){
            cnt--;
        }
        strncpy(loc.map[line],c,cnt);
        line++;
        
    }
    fclose(f);

    loc.map[height-1][width-1]='\0';    
}

void showMap(void){
    for(int i=0;i<height;i++){
        printf("%s",map[i]);
    }
}

void loc_putOnMap(void){
    memcpy(map,loc.map,sizeof(map));
}

void initPlayer(int x, int y){
    player.pos.x=x;
    player.pos.y=y;
}

void player_putOnMap(void){
    map[player.pos.y][player.pos.x]='A';
}