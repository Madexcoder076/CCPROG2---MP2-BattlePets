#include <stdio.h>
#define RED "\x1b[31m" // Text Color changer
#define RESET "\x1b[0m" 

int main(){

int nChoice = 0;
/*
    Main Menu Loop.
    Loop will only exit when 0 is inputted
*/
do{
    printf("Main Menu\n");
    printf("[1] Battle\n");
    printf("[2] ComPetDium\n");
    printf("[3] View Statistcs\n");
    printf("[0] Exit\n");
    printf(">> ");
    scanf("%d", &nChoice);
    if(nChoice < 0 || nChoice > 3){ // Take out invalid choices
        printf(RED"Invalid Choice! Please try again"RESET"\n");
        nChoice = -1;
    }
    if(nChoice == 1){
        printf("Player chose battle\n");
    }
    else if(nChoice == 2){
        printf("Player chose ComPetDium\n");
    }
    else if(nChoice == 3){
        printf("Player is viewing Statistics\n");
    }
    else{
        printf("Exiting...");
}
}while (nChoice!= 0);



    
return 0;
}
