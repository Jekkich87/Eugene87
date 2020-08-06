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

typedef struct{
    char name[20];
}TItem;

struct{
    char name[20];
    POINT pos;
    POINT locPos;
    TItem items[20];
}player;

typedef struct{
    char name[20];
    char oType;
    POINT pos;
    char item_Message[200];
    TItem item_Need;
    int item_CNT;
    TItem item_Given;
}TObj;

                                              // 

TObj* obj=NULL;
int objCNT=0;

char map[height][width+1];

void loc_LoadFormFile(char* filename);               // function to loading location from file
void showMap(void);                                  // function for displaying map
void loc_putOnMap(void);

void initPlayer(int xLoc,int yLoc,int x, int y,char* name);
void player_putOnMap(void);
void player_Control(void);
void player_SavePos(void);
void player_LoadPos(char* name);
void player_LoadLoc();

TObj* obj_Add(void);                                // adding objects on map;
void obj_LoadFromFile(char* name);                  // downloading objects on map
void obj_PutOnMap(void);
TObj* obj_GetByXY(int x,int y);                     // receiving coordinations about objects (NPC and doors)
void obj_StartDialog(TObj* obj);                    // starting dialog with npc

int player_ItemCount(TItem item);                  // counting how many need items plaer has
void player_GetItem(TItem item);                   // getting item form NPC
int player_GiveItems(TItem item, int delCNT);      // player gives items to NPC

void setCursor(int x,int y);
void hideCursor(void);


int main(void) {

    
    system("cls");
    system("mode 80,25");
    system("mode con cols=80 lines=25");

    hideCursor();

    player_LoadPos("Player");
    player_LoadLoc(); 

    do{
        player_Control();
        loc_putOnMap();
        obj_PutOnMap();      
        player_putOnMap();
        showMap();
        Sleep(50);

    }while(GetKeyState(VK_ESCAPE)>=0);

    player_SavePos();

    return 0;
}

void loc_LoadFormFile(char* filename){

    memset(&loc.map,' ',sizeof(loc));                 // filling in the map by space char;
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
    memset(player.items,0,sizeof(player.items));
}

void player_putOnMap(void){
    map[player.pos.y][player.pos.x]='A';

    static int dx=55;
    for(int k=0;k<20;k++){
        for(int i=0;i<20;i++){
            if((player.items[k].name[i]!=0)&&(player.items[k].name[i]!='\n')){
                map[k][dx+i]=player.items[k].name[i];
            }
        }
    }
}

void player_Control(void){

    POINT old=player.pos;
    if(GetKeyState(VK_UP)<0){player.pos.y--;}
    if(GetKeyState(VK_DOWN)<0){player.pos.y++;}
    if(GetKeyState(VK_LEFT)<0){player.pos.x--;}
    if(GetKeyState(VK_RIGHT)<0){player.pos.x++;}
    if(map[player.pos.y][player.pos.x]!=' '){

        if(map[player.pos.y][player.pos.x]=='a'){
            TItem item;
            sprintf(item.name,"Apple");
            player_GetItem(item);
            Sleep(500);
        }

        TObj* obj=obj_GetByXY(player.pos.x,player.pos.y);
        player.pos=old;
        obj_StartDialog(obj);

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

    sprintf(c,"obj_%d_%d.txt",player.locPos.x,player.locPos.y);
    obj_LoadFromFile(c);

}

TObj* obj_Add(void){
    objCNT++;
    obj=realloc(obj,sizeof(*obj)*objCNT);
    return obj+objCNT-1;
}

void obj_LoadFromFile(char* name){
    objCNT=0;
    obj=realloc(obj,0);
    TObj* tmp;

    FILE* f=fopen(name,"rt");

    if(f){
        while(!feof(f)){
            tmp=obj_Add();
            fgets(tmp->name,1000,f);
            fscanf(f,"%c",&tmp->oType);
            fscanf(f,"%d",&tmp->pos.x);
            fscanf(f,"%d\n",&tmp->pos.y);

            fgets(tmp->item_Message,1000,f);
            fgets(tmp->item_Need.name,1000,f);
            fscanf(f,"%d\n",&tmp->item_CNT);

            fgets(tmp->item_Given.name,1000,f);
            int len=strlen(tmp->item_Given.name);
            if(tmp->item_Given.name[len-1]=='\n'){
                tmp->item_Given.name[len-1]=='\0';
            }
        }
    }
    fclose(f);
}

void obj_PutOnMap(void){
    for(int i=0;i<objCNT;i++){
        map[obj[i].pos.y][obj[i].pos.x]=obj[i].oType;
    }
}

TObj* obj_GetByXY(int x,int y){
    for(int i=0;i<objCNT;i++){
        if((obj[i].pos.x==x)&&(obj[i].pos.y==y)){
            return obj+i;
        }
        
    }
    return NULL;
}

void obj_StartDialog(TObj* obj){
    if(obj==NULL){
        return;
    }

    char answ;

    do{

        system("cls");
        printf("%s\n",obj->name);

        if(obj->oType=='/'){

            if(player_ItemCount(obj->item_Need)<obj->item_CNT){
                printf("\n%s\n",obj->item_Message);
                printf("0-Exit\n");
                answ=getch();
            }

            else{
                printf("\nEnter the door?\n");
                printf("1 - Yes\n");
                printf("0 - No");
                answ=getch();
                if(answ=='1'){
                    player.pos.x+=(obj->pos.x-player.pos.x)*2;
                    player.pos.y+=(obj->pos.y-player.pos.y)*2;
                    answ='0';
                }
            }       
            
        }

        else if(obj->oType=='N'){

            if(player_ItemCount(obj->item_Need)<obj->item_CNT){
                printf("\n%s\n",obj->item_Message);
                printf("0-Exit\n");
                answ=getch();
            }

            else{
                printf("\nNeed a %s?\n",obj->item_Given.name);
                printf("1 - Yes\n");
                printf("0 - No");
                answ=getch();
                if(answ=='1'){
                    TItem item;
                    sprintf(item.name,obj->item_Given.name);
                    if((player_ItemCount(item)==0)&&(player_GiveItems(obj->item_Need,obj->item_CNT)>0)){
                        player_GetItem(item);
                    }
                    answ='0';
                }

            }
        }

        else{
            answ='0';
        }

    }while(answ!='0');

}

int player_ItemCount(TItem item){
    int cnt=0;
    int len=strlen(item.name);
    if(item.name[len-1]=='\n'){
        len--;
    }
    for(int i=0;i<20;i++){
        if(strncmp(item.name,player.items[i].name,len)==0){
            cnt++;
        }
    }
    return cnt;
}

void player_GetItem(TItem item){
    for(int i=0;i<20;i++){
        if(player.items[i].name[0]==0){
            sprintf(player.items[i].name,item.name);
            return;
        }
    }
}

int player_GiveItems(TItem item, int delCNT){
    int cnt=player_ItemCount(item);
    if(delCNT>cnt) {return 0;}
    int len=strlen(item.name);
    if(item.name[len-1]=='\n'){
        len--;
    }
    for(int i=0;i<20;i++){
        if(strncmp(item.name,player.items[i].name,len)==0){
            memset(player.items[i].name,0,sizeof(player.items[i].name));
            delCNT--;
            if(delCNT<1){
                return 1;
            }
        }
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