/*
 * moves.h
 *
 *  Created on: 13 Apr 2017
 *      Author: Eddie
 */

#ifndef MOVES_H_
#define MOVES_H_



#endif /* MOVES_H_ */

typedef int bool;
enum {false,true};

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
