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
	w =50;
	z = 50;
	int now;
	for(f=0;f<=set-1;f++){
		if(players[f].slots==players[o].slots+victim){
			printf("\nPlayer %d: %s",f+1,players[f].first_name);
			z=f;
			now = f;
		}
		if(players[f].slots==players[o].slots-victim){
			printf("\nPlayer %d: %s",f+1,players[f].first_name);
			w=f;
			now = f;
		}
	}
		if(now==z&&now==w){
		printf("\nEnter the number of the player you would like to attack either %d or %d: ", z+1,w+1);
		scanf("%d",&person);
		person--;
		}
		if(now==z && now!=w){
		printf("\nEnter the number of the player you would like to attack %d: ", z+1);
		scanf("%d",&person);
		person--;
		}
		if(now!=z&&now==w){
		printf("\nEnter the number of the player you would like to attack %d: ", w+1);
		scanf("%d",&person);
		person--;
		}
	
	if(players[person].strength<=70){
		players[person].life_points=players[person].life_points-(int)(0.5*players[o].strength);
	}
	else if(players[person].strength>70){
		players[person].life_points=players[person].life_points-(int)(0.3*players[o].strength);
	}
}
void move(struct Player players[],struct slots array[],int slotnum, int o){
	int cantmove1 =0;//up 
	int cantmove2 = 0;//down
	int choice =50;
	if (players[o].slots==slotnum){
		cantmove1 =1;
	}
	if (players[o].slots==1){
		cantmove2 =1;
	}
														//finding what locations are available for each player
	if (cantmove1 ==0 && cantmove2 ==0){	
		printf("You can move to slots %d and %d\n",array[players[o].slots-2].slotposition,array[players[o].slots].slotposition);	
		printf("You can Move Down 1 Slot, Up 1 slot or stay in your current slot\n");
		printf("Press 1 to move down or 2 to move up or 0 to continue without moving\n");
		scanf("%d", &choice);
	}
	else if (cantmove1 ==1 && cantmove2 ==0){
		printf("You can move to slot %d.\n",array[players[o].slots-2].slotposition);
		printf("You can Move Down 1 Slot or stay in your current slot\n");
		printf("Press 1 to move down or 0 to continue without moving\n");
		scanf("%d", &choice);
	}
	else if (cantmove1 ==0 && cantmove2 ==1){
		printf("You can move to slot %d\n",array[players[o].slots].slotposition);
		printf("You can Move Up 1 Slot or stay in your current slot\n");
		printf("Press 2 to move up or 0 to continue without moving\n");
		scanf("%d", &choice);
	}
													//depending on possible moves print their options
													// and ask the user what they would like to do
	if(choice == 1){
		players[o].slots=array[players[o].slots-2].slotposition;
		strcpy(players[o].slotsT, array[players[o].slots-2].slottype);		//move the player
		if(players[o].slotsT[0] == 'H'){
			if (players[o].dexterity >= 60){
				players[o].strength=players[o].strength-10;
			}
			else if (players[o].dexterity <= 50){
				players[o].strength=players[o].strength+10;
			}
		}
		else if(players[o].slotsT[0]=='C'){
			if (players[o].smarts<=50){
				players[o].magic_skills=players[o].magic_skills+10;
			}	
			else if (players[o].smarts>60){
				players[o].dexterity=players[o].dexterity-10;
			}
		}
	}																			
	else if(choice == 2){
		players[o].slots=array[players[o].slots].slotposition;
		strcpy(players[o].slotsT, array[players[o].slots].slottype);
		if(players[o].slotsT[0] == 'H'){
			if (players[o].dexterity >= 60){
				players[o].strength=players[o].strength-10;
			}
			else if (players[o].dexterity <= 50){
				players[o].strength=players[o].strength+10;
			}
		}	
		else if(players[o].slotsT[0]=='C'){
			if (players[o].smarts<=50){
				players[o].magic_skills=players[o].magic_skills+10;
			}
			else if (players[o].smarts>60){
				players[o].dexterity=players[o].dexterity-10;
			}
		}
	}														//implement skill changes
	printf("New position of the player is %d, %s\n\n", players[o].slots, players[o].slotsT); //print out new locations
}
			