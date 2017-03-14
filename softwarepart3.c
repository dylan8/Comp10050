#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>



char arr[7][3][20];



const char *One = "Elf";
const char *Two = "Human";
const char *Three = "Ogre";
const char *Four = "Wizard";        //set 4 strings for comparison to possible types of player

struct Player {
    char first_name[50];
    char second_name[50];
    int life_points;
    int dexterity;
    int luck;
    int magic_skills;
    int smarts;
    int strength;
    int slots;
    char slotsT[50];
};                                  //struct set up for player

struct slots{
    char slottype[50];
    int slotposition;
};                                  //struct set up for slots

void attack(struct Player players[],int set,int slotnum, int o);
int * getCharacteristics(char *type);
void makeslots(struct slots *array, int coop);      //initialize functions


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
    struct Player players[numPlay];             //set up array of structs Player

    printf("Now Please Enter The Names of Players Playing\n");

    for (i=0; i<numPlay; i++){
        scanf("%s", &players[i].first_name);
    }                                                                   //scan in number of players playng and their names

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

    }                                   //scan in number which is used to assign second name

    int *p;

    for (i = 0; i <numPlay; i++){
        for (j =0; j <= 4; j++){
            p = getCharacteristics(players[i].second_name);
            if (j ==0){
                players[i].luck = *(p);
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
            }                           //not sure this works was meant to use pointer to the array from the function but i was not sure if this is how to correctly get each value properly
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
                                                            //print out all the players details
    printf("How many slots wish to be inputed?\n");
    scanf("%d", &numSlot);
    while(numSlot>20 || numSlot<numPlay){
        printf("Slots must be between %d and 20\n", numPlay);
        scanf("%d", &numSlot);
    }                                                       //scan in number of slots
    struct slots array[numSlot];                            //make array of structs for Slots
    makeslots(array, numSlot);                              //call function to make slots

    int pup, randomnumber, arraytest[6];
    int same = 1;
    int Continue = 1;

    for(pup=0;pup<numPlay;pup++){
        randomnumber=rand()%numSlot;

        while(same ==1){
            same = 0;
            for(int k=0;k<numPlay+1;k++){
                if(arraytest[k] == randomnumber){
                    same = 1;
                }
            }
        }
        players[pup].slots=array[randomnumber].slotposition;
        strcpy(players[pup].slotsT,array[randomnumber].slottype);
        arraytest[pup] = randomnumber;
    }                                               //get information from slots into necessary locations in player structs
    while(Continue ==1){                                    //loop to allow game to have numerous turs
        for(pup=0;pup<numPlay;pup++){
            printf("Player %s is in slot %d,%s\n", players[pup].first_name,players[pup].slots, players[pup].slotsT);
        }                                               //display player location and slot type
        int cantmove1, cantmove2, choice;

        for(pup=0;pup<numPlay;pup++){
            cantmove1 = 0, cantmove2=0;
            printf("Player %s turn.\n", players[pup].first_name);

            for (int wat = 0; wat <= numPlay; wat++) {
                if (players[pup].slots+1==players[wat].slots){
                    cantmove1=1;
                }
                if (players[pup].slots-1==players[wat].slots){
                cantmove2=1;
                }
            }
                                                        //finding what locations are available for each player
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
            }                                           //depending on possible moves print their options

            printf("Do you want to move up or down a step?\n");
            printf("Press numbers 1 for down or 2 for up\n");
            scanf("%d", &choice);                       // ask the user what they would like to do
            if(choice == 1 && cantmove1 == 0){
                players[pup].slots=array[players[pup].slots-2].slotposition;
                strcpy(players[pup].slotsT, array[players[pup].slots-2].slottype);      //move the player
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
            }                                                       //implement skill changes
            printf("New position of the player is %d, %s\n\n", players[pup].slots, players[pup].slotsT); //print out new locations
        }
        for(i = 0; i< numPlay; i ++){
            attack(players, numPlay, numSlot,  i);
            if (players[i].life_points <= 0){
                printf("\n\n%s %s has passed way in combat\n\n", players[i].first_name, players[i].second_name);
                for(i; i<= numPlay; i++){
                    players[i]= players[i+1];
                    numPlay --;
                    if (numPlay == 1){
                        printf("The Game is Over as We only Have One Contestent remaining!\n\n");
                        printf("Let Me Pronounce Todays Winner: %s %s", players[0].first_name, players[0].second_name);
                        for (i=0; i<numPlay; i++){
                            printf("%s %s\n", players[i].first_name,players[i].second_name);
                            printf("Luck is equal to  %d\n", players[i].luck);
                            printf("Dexterity is equal to  %d\n", players[i].dexterity);
                            printf("Smarts is equal to  %d\n", players[i].smarts);
                            printf("Strength is equal to  %d\n", players[i].strength);
                            printf("Magic is equal to  %d\n", players[i].magic_skills);
                            printf("They have the following life points %d\n", players[i].life_points);
                            printf("The Player Ended in Slot %d of type %s\n", players[i].slots, players[i].slotsT);
                            printf("\n\n");

                        }
                        return 0;
                    }
                }
            }
        }

        printf("Please Enter 1 to continue playing or any other number to end\n\n");
        scanf("%d", & Continue);                                //ask user if they want to continue
    }
    printf("The Final Results Are.\n");
    for (i=0; i<numPlay; i++){
        printf("%s %s\n", players[i].first_name,players[i].second_name);
        printf("Luck is equal to  %d\n", players[i].luck);
        printf("Dexterity is equal to  %d\n", players[i].dexterity);
        printf("Smarts is equal to  %d\n", players[i].smarts);
        printf("Strength is equal to  %d\n", players[i].strength);
        printf("Magic is equal to  %d\n", players[i].magic_skills);
        printf("They have the following life points %d\n", players[i].life_points);
        printf("The Player Ended in Slot %d of type %s\n", players[i].slots, players[i].slotsT);
        printf("\n\n");
    }
                                                                //print out the final results
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
        c[1] = rand ()%20 + 80;
        c[3] = rand ()%20 + 80;
        c[4] = 0;
        sumtotal = 100;
        while(sumtotal > 50){
            c[2] = rand ()%19 +1;
            c[0] = rand ()%99 +1;
            sumtotal =c[0]+ c[2] ;
        }
    }
    if (strcmp(type, Four) == 0){
        c[0] = rand ()%50 +50;
        c[1] = rand ()%99 +1;
        c[2] = rand ()%10 +90;
        c[3] = rand ()%19 +1;
        c[4] = rand ()%20 +80;
    }

    return c;

}

void makeslots(struct slots *array, int coop){
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


void attack(struct Player players[],int set,int slotnum, int o){
    int j,f,k,z=0,w=0,q;
    int person,diff=0,victim;
    unsigned int other=22;
    for(f=0;f<=set-1;f++){
        diff=players[o].slots-players[f].slots;

        if(diff<0){
            diff=diff*(-1);
        }
        if(diff<other&&diff!=0){
            victim=diff;
            other=diff;
        }
        if(diff!= 0){
            printf("\n%s is %d slots away:",players[f].first_name, diff);
        }
    }
    other=set-1;
    printf("\n%s, player %d is allowed to attack:",players[o].first_name,o+1);
    for(f=0;f<=set-1;f++){
        if(players[f].slots==players[o].slots+victim){
            printf("\nPlayer %d: %s",f+1,players[f].first_name);
            z=f;
        }
        if(players[f].slots==players[o].slots-victim){
            printf("\nPlayer %d: %s",f+1,players[f].first_name);
            w=f;
        }
        if(w == f || z == f){}
        else{
            printf("\nNobody! Please Enter 0 to Continue");
        }
    }
    printf("\nEnter the number of the player you would like to attack: ");
    scanf("%d",&person);
    person = person -1;
    if(person==z||person==w){}
    else{
        printf("\nError.");
        printf("\nEnter the number of the player you would like to attack either %d or %d: ", z,w);
        scanf("%d",&person);
        person = person-1;
    }
    if(players[person].strength<=70){
        players[person].life_points=players[person].life_points-(int)(0.5*players[o].strength);
    }
    else if(players[person].strength>70){
        players[o].life_points=players[o].life_points-(int)(0.3*players[o].life_points);
    }
}
