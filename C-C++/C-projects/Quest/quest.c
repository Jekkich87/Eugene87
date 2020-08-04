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
    POINT size;
}loc;

struct{
    char name[20];
    POINT pos;
    POINT locPos;
}player;

char map[height][width+1];

void loc_LoadFormFile(char* filename);              // function to loading location from file
void showMap(void);                                 // function for displaying map
void loc_putOnMap(void);

void initPlayer(int xLoc,int yLoc,int x, int y,char* name);
void player_putOnMap(void);

void player_Control(void);
void player_SavePos(void);
void player_LoadPos(char* name);
void player_LoadLoc();

void setCursor(int x,int y);
void hideCursor(void);


int main(void) {

    
    system("cls");
    system("mode 80,25");
    system("mode con cols=80 lines=25");

    player_LoadPos("Player");
    player_LoadLoc(); 

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

    memset(&loc.map,' ',sizeof(loc));            // filling in the map by space char;
    for(int i=0;i<height;i++){
        loc.map[i][width]='\0';
    }
    FILE* f=fopen(filename,"r");
    char c[80];
    int line=0;
    loc.size.x=0;
    loc.size.y=0;
    while(!feof(f)){
        fgets(c,width,f);
        int cnt=strlen(c);
        if(c[cnt-1]=='\n'){
            cnt--;
        }
        strncpy(loc.map[line],c,cnt);
        line++;
        if(cnt>loc.size.x-2){
            loc.size.x=cnt;
        }
        loc.size.y=line;
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

void initPlayer(int xLoc,int yLoc,int x, int y,char* name){

    player.pos.x=x;
    player.pos.y=y;
    sprintf(player.name,name);
    player.locPos.x=xLoc;
    player.locPos.y=yLoc;
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
    if(player.pos.x>(loc.size.x-2)){                          // if player leave current location, new location will be downloaded.
        player.locPos.x++;
        player_LoadLoc();
        player.pos.x=1;
    }
    if(player.pos.x<1){                          
        player.locPos.x--;
        player_LoadLoc();
        player.pos.x=loc.size.x-2;
    }
    if(player.pos.y>(loc.size.y-2)){                          // if player leave current location, new location will be downloaded.
        player.locPos.y++;
        player_LoadLoc();
        player.pos.y=1;
    }
    if(player.pos.y<1){                          
        player.locPos.y--;
        player_LoadLoc();
        player.pos.y=loc.size.y-2;
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
        initPlayer(0,0,5,5,name);
    }
    else{
        fread(&player,1,sizeof(player),f);
    }
    fclose(f);
}

void player_LoadLoc(){
    char c[100];
    sprintf(c,"map_%d_%d.txt",player.locPos.x,player.locPos.y);
    loc_LoadFormFile(c);
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