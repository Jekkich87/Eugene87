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
    char name[20];
    POINT pos;
}player;

char map[height][width+1];

void loc_LoadFormFile(char* filename);              // function to loading location from file
void showMap(void);                                 // function for displaying map
void loc_putOnMap(void);

void initPlayer(int x, int y,char* name);
void player_putOnMap(void);

void player_Control(void);
void player_SavePos(void);
void player_LoadPos(char* name);

void setCursor(int x,int y);
void hideCursor(void);


int main(void) {

    
    system("cls");
    system("mode 80,25");
    system("mode con cols=80 lines=25");

    loc_LoadFormFile("map_0_0.txt");
    player_LoadPos("Player");

    do{
        player_Control();
        loc_putOnMap();      
        player_putOnMap();
        showMap();
        Sleep(50);

    }while(GetKeyState(VK_ESCAPE)>=0);

    player_SavePos();

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
    setCursor(0,0);

    for(int i=0;i<height;i++){
        printf("%s",map[i]);
    }
}

void loc_putOnMap(void){
    memcpy(map,loc.map,sizeof(map));
}

void initPlayer(int x, int y,char* name){
    player.pos.x=x;
    player.pos.y=y;
    sprintf(player.name,name);
}

void player_putOnMap(void){
    map[player.pos.y][player.pos.x]='A';
}

void player_Control(void){

    POINT old=player.pos;
    if(GetKeyState(VK_UP)<0){player.pos.y--;}
    if(GetKeyState(VK_DOWN)<0){player.pos.y++;}
    if(GetKeyState(VK_LEFT)<0){player.pos.x--;}
    if(GetKeyState(VK_RIGHT)<0){player.pos.x++;}
    if(map[player.pos.y][player.pos.x]!=' '){
        player.pos=old;
    }
}

void player_SavePos(void){

    FILE* f=fopen(player.name,"wb");
    fwrite(&player,1,sizeof(player),f);
    fclose(f);

}

void player_LoadPos(char* name){
    FILE* f=fopen(name,"rb");
    if(f==NULL){
        initPlayer(5,5,name);
    }
    else{
        fread(&player,1,sizeof(player),f);
    }
    fclose(f);
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