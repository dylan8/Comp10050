#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

const char *One = "Elf";
const char *Two = "Human";
const char *Three = "Ogre";
const char *Four = "Wizard";		//set 4 strings for comparison to possible types of player

struct Player {
	char first_name[50];
	char second_name[50];
	int	life_points;
	int	dexterity;
	int luck; 
	int magic_skills;
	int smarts;
	int strength;
	int slots;
	char slotsT[50];
};									//struct set up for player

struct slots{
	char slottype[50];
	int slotposition;
};									//struct set up for slots

void attack(struct Player players[],int set,int slotnum, int o);
int * getCharacteristics(char *type);
void makeslots(struct slots *array, int coop);		//initialize functions
void move(struct Player players[],struct slots array[], int slotnum, int o);

int main(void) {
	
	srand(time(NULL));		
	int i =0;
	int j;
	int numPlay;
	int typePlay;
	int numSlot;
	
	printf("Please Enter The Number of Players Playing (Max 6)\n");
	scanf("%d", &numPlay);
	
	struct Player players[numPlay];				//set up array of structs Player
	
	printf("Now Please Enter The Names of Players Playing\n");
	
	for (i=0; i<numPlay; i++){
		scanf("%s", &players[i].first_name);
	}																	//scan in number of players playng and their names
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
		
	}									//scan in number which is used to assign second name
	
	int *p;
	for (i = 0; i <numPlay; i++){		
		for (j =0; j <= 4; j++){
			p = getCharacteristics(players[i].second_name);
			if (j ==0){
				players[i].luck = *(p+j);
			}
			if (j ==1){
				players[i].dexterity = *(p+j);
			}
			if (j ==2){
				players[i].smarts = *(p+j);
			}
			if (j ==3){
				players[i].strength = *(p+j);
			}
			if (j ==4){
				players[i].magic_skills = *(p+j);
			}						
			players[i].life_points = 100;				//assign players chracteristics and life points
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
	}														//print out all the players details
	printf("How many slots wish to be inputed?\n");
	scanf("%d", &numSlot);
	while(numSlot>20 || numSlot<numPlay){
		printf("Slots must be between %d and 20\n", numPlay);
		scanf("%d", &numSlot);
	}														//scan in number of slots
	struct slots array[numSlot];							//make array of structs for Slots
	makeslots(array, numSlot);								//call function to make slots
	
	int pup, randomnumber, arraytest[6];
	int same = 1;
	int Continue = 1;
	
	while (same ==1){
		for(pup=0;pup<=numPlay;pup++){
			randomnumber=rand()%numSlot;
			players[pup].slots=array[randomnumber].slotposition;
			strcpy(players[pup].slotsT,array[randomnumber].slottype);
			arraytest[pup] = randomnumber;
			for(int k=0;k<numPlay;k++){
				for (j = 0; j <= numPlay; j++){
					if (k != j){
						if (players[j].slots == players[k].slots){
							same = 20000;
						}
					}
				}
			}
		}
		if (same == 20000){
			same =1;
		}
		else {
			same =5;
		}
	}					//get information from slots into necessary locations in player structs
	while(Continue ==1){									//loop to allow game to have numerous turs
		for(pup=0;pup<numPlay;pup++){
			printf("Player %s is in slot %d,%s\n", players[pup].first_name,players[pup].slots, players[pup].slotsT);
		}												//display player location and slot type
		
		int moveor = 50;
		for(pup=0;pup<numPlay;pup++){	
			printf("Player %s turn.\n", players[pup].first_name);
			printf("Would You Like To Move Or Attack\n");
			printf("Please Enter 1 To Move Or 2 To Attack\n");
			scanf("%d", &moveor);
	
			
			if (moveor == 1){
				move(players, array, numSlot, pup);
			}
			
			if (moveor == 2){
				attack(players, numPlay, numSlot,  pup);
			}
		}
		for (j = 0; j<=numPlay; j++){
			if (players[j].life_points <= 0){
				printf("\n\n%s %s has passed way in combat\n\n", players[j].first_name, players[j].second_name);
				for(i; i<= numPlay; i++){
					players[i]= players[i+1];
					numPlay --;
					if (numPlay == 1){
						printf("The Game is Over as We only Have One Contestent remaining!\n\n");
						printf("Let Me Pronounce Todays Winner: %s ", players[0].first_name);
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
							return 0;
						}
					}	
				}
			}
		}
		
		
		printf("Please Enter 1 to continue playing or any other number to end\n\n");
		scanf("%d", & Continue);								//ask user if they want to continue
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

	

