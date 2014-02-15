#include "carte.h"
#include "robot.h"
#include "graphique.h"
#include "appart.h"

int main(){
	char map[LG_APPART][HT_APPART];
	int i,j,choix=0;
	Init_carte (appart, map);// Initialisation de la carte
	
	system ("clear");//plus rien dans la console
	
	for (i=0;i<HT_APPART;i++){ //affiche de la carte à lancer
		for(j=0;j<LG_APPART;j++){
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
	 //choix du type d'affichage
	 printf("\nVeuillez selectionner 1 pour un affichage en console, et 2 pour un affichage graphique:\n");
	scanf("%d", &choix);
	
	
	Graph gr = debut(choix);	//initialise ma fenêtre

	DeplacementRobot(map, choix, gr); //affichage en console
	
	
	
	if(choix!=1 || choix!=2) printf("Votre demande ne peut aboutir veuillez redémarrer le programme pour rééssayer");
}
