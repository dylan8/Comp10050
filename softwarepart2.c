#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>



char arr[7][3][20];

int * getCharacteristics(char *type);

const char *One = "Elf";
const char *Two = "Human";
const char *Three = "Ogre";
const char *Four = "Wizard";

struct Player {
    char first_name[50];
    char second_name[50];
    int life_points;
    int dexterity;
    int luck;
    int magic_skills;
    int smarts;
    int strength;
    int position;
    int slots;
    char slotsT[50];
}tempPlay;

struct slots{
    char slottype[50];
    int slotposition;
};

void makeMove (struct Player tempPlay);
void makeslots(struct slots *array, int anna);


int main(void) {

    srand(time(NULL));
    int i =0;
    int j;
    char player[10][2][20];
    char blank[100];
    int numPlay;
    int typePlay;
    int numSlot;

    printf("Please Enter The Number of Players Playing (Max 6)\n");

    scanf("%d", &numPlay);
    struct Player players[numPlay];


    printf("Now Please Enter The Names of Players Playing\n");

    for (i=0; i<numPlay; i++){

        scanf("%s", &players[i].first_name);
    }

    printf("\n\nFor The Following Please enter\n1 for Type: Elf\n2 for Type: Human\n3 for Type: Ogre\n4 for Type: Wizrd\n");
    for (i=0; i<numPlay; i++){
        printf("Now Please Enter The Type of %s\n", players[i].first_name);
        scanf("%d", &typePlay);

        if (typePlay == 1){
            sscanf(One, "%s", players[i].second_name);
        }
        if (typePlay == 2){
            sscanf(Two, "%s", players[i].second_name);
        }
        if (typePlay == 3){
            sscanf(Three,"%s", players[i].second_name);
        }
        if (typePlay == 4){
            sscanf(Four, "%s", players[i].second_name);
        }

    }

    int *p;

    for (i = 0; i <numPlay; i++){
        for (j =0; j <= 4; j++){
            p = getCharacteristics(players[i].second_name);
            if (j ==0){
                players[i].luck = *(p+j);
            }
            if (j ==1){
                players[i].dexterity = *(p);
            }
            if (j ==2){
                players[i].smarts = *(p);
            }
            if (j ==3){
                players[i].strength = *(p);
            }
            if (j ==4){
                players[i].magic_skills = *(p);
            }
            players[i].life_points = 100;
        }
    }
    printf("The Players Are:\n");
    for (i=0; i<numPlay; i++){
        printf("%s %s\n", players[i].first_name,players[i].second_name);
        printf("Luck is equal to  %d\n", players[i].luck);
        printf("Dexterity is equal to  %d\n", players[i].dexterity);
        printf("Smarts is equal to  %d\n", players[i].smarts);
        printf("Strength is equal to  %d\n", players[i].strength);
        printf("Magic is equal to  %d\n", players[i].magic_skills);
        printf("They have the following life points %d\n", players[i].life_points);
        printf("\n\n");
    }

    printf("How many slots wish to be inputed?\n");
    scanf("%d", &numSlot);
    while(numSlot>20 || numSlot<numPlay){
        printf("Slots must be between %d and 20\n", numPlay);
        scanf("%d", &numSlot);
    }
    struct slots array[numSlot];
    makeslots(array, numSlot);

    int pup, randomnumber, arraytest[6];
    int same = 1;
    for(pup=0;pup<numPlay;pup++){
        randomnumber=rand()%numSlot;

        while(same ==1){
        same = 0;

        for(int k=0;k<numPlay+1;k++){

            if(arraytest[k] == randomnumber)
                same = 1;
            }
        }
        players[pup].slots=array[randomnumber].slotposition;
        strcpy(players[pup].slotsT,array[randomnumber].slottype);
        arraytest[pup] = randomnumber;
    }

    for(pup=0;pup<numPlay;pup++){
        printf("Player %s is in slot %d,%s\n", players[pup].first_name,players[pup].slots, players[pup].slotsT);
    }
    int cantmove1, cantmove2, choice;

    for(pup=0;pup<numPlay;pup++){
        cantmove1 = 0, cantmove2=0;
        printf("Player %s turn.\n", players[pup].first_name);

        for (int kit = 0; kit < numPlay+1; kit++) {
            if (players[pup].slots+1==players[kit].slots){
                cantmove1=1;
            }
            if (players[pup].slots-1==players[kit].slots){
            cantmove2=1;
            }
        }

        if (cantmove1 ==0 && cantmove2 ==0){
            printf("You can move to slots %d and %d\n",array[players[pup].slots-2].slotposition,array[players[pup].slots].slotposition);
        }
        else if (cantmove1 ==1 && cantmove2 ==0){
            printf("You can move to slot %d.\n",array[players[pup].slots-2].slotposition);
        }
        else if (cantmove1 ==0 && cantmove2 ==1){
            printf("You can move to slot %d\n",array[players[pup].slots].slotposition);
        }
        else if (cantmove1 ==1 && cantmove2 ==1){
            printf("You cant move to any slots\n");
        }

        printf("Do you want to move up or down a step?\n");
        printf("Press numbers 1 for down or 2 for up\n");
        scanf("%d", &choice);
        if(choice == 1 && cantmove1 == 0){
            players[pup].slots=array[players[pup].slots-2].slotposition;
            strcpy(players[pup].slotsT, array[players[pup].slots-2].slottype);
            if(players[pup].slotsT[0] == 'H'){
                if (players[pup].dexterity >= 60){
                    players[pup].strength=players[pup].strength-10;
                }
                else if (players[pup].dexterity <= 50){
                    players[pup].strength=players[pup].strength+10;
                }
            }
            else if(players[pup].slotsT[0]=='C'){
                if (players[pup].smarts<=50){
                    players[pup].magic_skills=players[pup].magic_skills+10;
                }
                else if (players[pup].smarts>60){
                    players[pup].dexterity=players[pup].dexterity-10;
                }
            }
        }
        else if(choice == 2 && cantmove2 == 0){
            players[pup].slots=array[players[pup].slots].slotposition;
            strcpy(players[pup].slotsT, array[players[pup].slots].slottype);
            if(players[pup].slotsT[0] == 'H'){
                if (players[pup].dexterity >= 60){
                    players[pup].strength=players[pup].strength-10;
                }
                else if (players[pup].dexterity <= 50){
                    players[pup].strength=players[pup].strength+10;
                }
            }
            else if(players[pup].slotsT[0]=='C'){
                if (players[pup].smarts<=50){
                    players[pup].magic_skills=players[pup].magic_skills+10;
                }
                else if (players[pup].smarts>60){
                    players[pup].dexterity=players[pup].dexterity-10;
                }
            }
        }
        printf("New position of the player is %d, %s\n\n", players[pup].slots, players[pup].slotsT);
    }
    return 0;
}

int * getCharacteristics(char *type){
    static int  c[4];
    int sumtotal =1000;
    if (strcmp(type, One) == 0){
        c[0] = rand ()%40 +60;
        c[1] = rand ()%99 +1;
        c[2] = rand ()%30 + 70;
        c[3] = rand ()%49 +1;
        c[4] = rand ()%28 +51;
    }
    if (strcmp(type, Two) == 0){
        while (sumtotal>=300){
            c[0] = rand ()%99 +1;
            c[1] = rand ()%99 +1;
            c[2] = rand ()%99 +1;
            c[3] = rand ()%99 +1;
            c[4] = rand ()%99 +1;
            sumtotal = c[0] +c[1] +c[2] +c[3]+ c[4];
        }
    }
    if (strcmp(type, Three) == 0){
        c[1] = rand ()%20+ 80;
        c[3] = rand ()%20+80;
        c[4] = 0;

        while(sumtotal > 50){
            c[2] = rand ()%19 +1;
            c[0] = rand ()%99 +1;
            sumtotal =c[0]+ c[2] ;
        }
    }
    if (strcmp(type, Four) == 0){
        c[9] = rand ()%50 +50;
        c[1] = rand ()%99 +1;
        c[2] = rand ()%10 +90;
        c[3] = rand ()%19 +1;
        c[4] = rand ()%20 +80;
    }

    return c;

}

void makeslots(struct slots *array, int coop)
{
    //srand(time(NULL));
    int x,z;
    for(x=0; x<coop; x++){
        z=rand()%3;
        if (z==0) {
            strcpy(array[x].slottype,"Ground");
        }
        else if (z==1){
            strcpy(array[x].slottype,"City");
        }
        else if (z==2){
            strcpy(array[x].slottype,"Hill");
        }
            array[x].slotposition = x+1;
        }
        for(x=0; x<coop; x++){
            printf("%d.%s\n",array[x].slotposition, array[x].slottype);
        }
}
