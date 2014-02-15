#ifndef ROBOT_H
#define ROBOT_H

typedef struct {
	int dir; // orientation
	int x; // position
	int y; // position
	} Robot;

#include "carte.h"
#include "graphique.h"


void Posdep(char map[LG_APPART][HT_APPART],Robot *posdep,Robot *posrobot);

void Posfin (char map[LG_APPART][HT_APPART], Robot *posfin);

void DeplacementRobot(char map[LG_APPART][HT_APPART], int choix, Graph gr);

int DetecteurSortie(Robot *posrobot,Robot *posfin, int compteur, char robot[LG_APPART][HT_APPART]);

void turn (Robot *posrobot, int rotation);

int obstacle (char map[LG_APPART][HT_APPART],Robot *posrobot);

void move (Robot *posrobot);

int NotSortie(Robot *posrobot,char robot[LG_APPART][HT_APPART],char map[LG_APPART][HT_APPART]);

#endif 

