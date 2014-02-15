#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "robot.h"

#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

struct graph {
	SDL_Surface *ecran;
	SDL_Surface *fond;
	SDL_Surface *wall;
	SDL_Surface *robot;
	SDL_Surface *sortie;
};

typedef struct graph Graph;

void init();

Graph debut(int choix);

void VerifEvenement(Graph gr);

void AfficheBlock (char car, int i, int j, int deb, Graph gr);

void texte_fin(Graph gr, int compteur);

#endif
