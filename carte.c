#include "carte.h"

void Init_carte (char*appart, char map[LG_APPART][HT_APPART]){ //on met le tableau à une dimension dans un tableau à deux dimensions
	memcpy(map,appart,LG_APPART*HT_APPART);
}

//--------------------------------------------------------------------------------------------------------------------

void AfficheLevel (char map[LG_APPART][HT_APPART], Robot *posrobot, int choix, int debut, Graph gr){
	int i,j;
	
	//affiche tout mon niveau que ce soit en console ou en graphique
	
	map[posrobot->y][posrobot->x]='R';
	for (i=0;i<HT_APPART;i++){
		for(j=0;j<LG_APPART;j++){
			if (choix==1) printf("%c",map[i][j]);
			if(choix ==2) AfficheBlock ( map[j][i],i,j, debut,gr);
		}
		if (choix==1) printf("\n");
	}
	
	usleep(18000);// attente avant de nettoyer l'ecran
	system ("clear");
	map[posrobot->y][posrobot->x]=' ';
}

//--------------------------------------------------------------------------------------------------------------------

void AfficheRobot (char robot[LG_APPART][HT_APPART]){ //fonction qui servait à montrer la carte faite par le robot
	int i,j;
	for (i=0;i<HT_APPART;i++){
		for(j=0;j<LG_APPART;j++){
			printf("%c",robot[i][j]);
		}
		printf("\n");
	}
}
