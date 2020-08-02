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

void loc_LoadFormFile(char* filename);              // function to loading location from file

int main() {

    system("cls");
    system("mode 80,25");
    system("mode con cols=80 lines=25");

    loc_LoadFormFile("map_0_0.txt");
    for(int i=0;i<height;i++){
        printf("%s",loc.map[i]);
    }
    return 0;
}

void loc_LoadFormFile(char* filename){

    //memset(&loc.map,' ',sizeof(loc));           // filling in the map by space char;
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