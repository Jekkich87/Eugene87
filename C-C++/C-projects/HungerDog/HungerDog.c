#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

int main(void) {

    char mas[10][21];    //Generating game field // Генерация игрового поля

    int i=0;
    int x=10,y=5;       // starting position for Dog
    int ox,oy;          //Dog`s position before move
    int ax=5,ay=3;      //starting position for apple
    int count=0;

    char key; //control key

    srand(time(NULL));

    do{
        sprintf(mas[0], "####################"); //Top border

        for(i=1;i<9;i++){
            sprintf(mas[i],"#                  #"); // side borders & inside field
        }

        sprintf(mas[9], "####################"); //Bottom border

        mas[y][x]='@'; // rendering dog in the field
        mas[ay][ax]='*';  // rendering apple in the field

        system("cls");  //clearing display;


        for(i=0;i<10;i++){  //Displaying game field //Отображаем игровое поле
            printf("%s\n",mas[i]);
        }

        printf("\n\n");
        printf("Count = %d",count); //counting of eated apples
        printf("\n\n");

        ox=x;
        oy=y; 

        key=getch();
        if(key==72) y--; // controling position of dog
        if(key==80) y++;
        if(key==75) x--;
        if(key==77) x++;

        if(mas[y][x]=='#'){
            x=ox;
            y=oy;
        }

        if(mas[y][x]==mas[ay][ax]){  //generating new position of apple
            ax=rand()*1.0/RAND_MAX*18+1;
            ay=rand()*1.0/RAND_MAX*8+1;
        }

    }while(key!=27);


    return 0;
}