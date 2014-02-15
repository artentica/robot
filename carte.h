#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "robot.h"
#include "graphique.h"
#define HT_APPART 50
#define LG_APPART 50
#define TAILLE_BLOC 14


void AfficheLevel (char map[LG_APPART][HT_APPART], Robot *posrobot, int choix, int debut, Graph gr);

void Init_carte (char* appart,char map[LG_APPART][HT_APPART]);

void AfficheRobot (char robot[LG_APPART][HT_APPART]);
