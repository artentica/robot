#include "robot.h"



void Posdep(char map[LG_APPART][HT_APPART],Robot *posdep,Robot *posrobot){//Trouve la position de départ du robot
	int i,j;
	for (i=0;i<HT_APPART;i++){
		for(j=0;j<LG_APPART;j++){
			if(map[i][j]=='D'){
				posdep->x=j;
				posdep->y=i;
				posrobot->x=j;
				posrobot->y=i;
			}
		}
	}
}


//--------------------------------------------------------------------------------------------------------------------

void Posfin (char map[LG_APPART][HT_APPART],Robot *posfin){//Trouve la position de sortie
	int i,j;
	for (i=0;i<HT_APPART;i++){
		for(j=0;j<LG_APPART;j++){
			if(map[i][j]=='S'){
				posfin->x=j;
				posfin->y=i;
			}
		}
	}
}


//--------------------------------------------------------------------------------------------------------------------

void DeplacementRobot(char map[LG_APPART][HT_APPART], int choix, Graph gr){
	//Initialisation des structs
	Robot posrobot, posfin, posdep;
	int i,j, compteur=0 , pledge=0, debut=1;
	char robot[LG_APPART][HT_APPART];
	srand(time(NULL));
	for (i=0;i<HT_APPART;i++){//je met des x sur le tour du labyrinthe et des " " ailleur
		for(j=0;j<LG_APPART;j++){
			if (j==0 || i==0 || j==49 || i==49) robot[i][j]='x';
			else robot[i][j]=' ';
		}
	}
	
	(posrobot.dir)=1;//(rand()%4);
	
	Posdep(map, &posdep, &posrobot);//position de départ
	Posfin(map, &posfin);//position de la sortie
	
	while(DetecteurSortie(&posrobot,&posfin, compteur, robot)){//Detection de proximité pour la sortie
	
		map[posrobot.y][posrobot.x]='1';
		
		AfficheLevel (map, &posrobot, choix, debut,gr);
		debut=0;
		if(NotSortie(&posrobot,robot,map)){//Si il est déjà passé par là
			while(obstacle(map,&posrobot) && (pledge%4 )==0 && DetecteurSortie(&posrobot,&posfin, compteur, robot)){//qu'il n'y a pas de mur et que pledge est un 
				move (&posrobot);							//multiple de 4 il va tout droit
				AfficheLevel (map, &posrobot, choix, debut, gr); //affiche la carte en sdl ou console
				VerifEvenement(gr); //vérifie si un argument a eu lieu
			}
		}
		
		
		
		if(obstacle(map,&posrobot)){//si pas d'obstacle j'avance
			move (&posrobot);
			turn (&posrobot, 0);
			pledge--;
		}
		
		else{//si un obstacle je tourne à droite
			turn(&posrobot, 1);
			pledge++;
		}
		VerifEvenement(gr);
		compteur++;// un tour de plus a était fait
	}
	texte_fin(gr, compteur);
}


//-------------------------------------------------------------------------------------------------------------------

int NotSortie(Robot *posrobot,char robot[LG_APPART][HT_APPART],char map[LG_APPART][HT_APPART]){
	//sert à faire une carte dans la mémoire du robot, je m'en sert pour la sortie des ilots
	robot[posrobot->y][posrobot->x]='1';

	switch (posrobot->dir){		
		case 0:
			if(map[posrobot->y-1][posrobot->x]=='x' || robot[posrobot->y-1][posrobot->x]=='0'){
				robot[posrobot->y-1][posrobot->x]='x';
			}
			if(robot[posrobot->y-1][posrobot->x]=='1'){
				return 1;
			}
			break;
			
		case 1:
			if(map[posrobot->y][posrobot->x+1]=='x' || robot[posrobot->y][posrobot->x+1]=='0'){
				robot[posrobot->y][posrobot->x+1]='x';
			}
			if(robot[posrobot->y][posrobot->x+1]=='1'){
				return 1;
			}
			break;
			
		case 2:
			if(map[posrobot->y+1][posrobot->x]=='1'){
				robot[posrobot->y+1][posrobot->x]='x';
			}
			if(robot[posrobot->y+1][posrobot->x]=='1'){
				return 1;
			}
			break;
			
		case 3:
			if(map[posrobot->y][posrobot->x-1]=='x' || robot[posrobot->y][posrobot->x-1]=='0'){
				robot[posrobot->y][posrobot->x-1]='x';
			}
			if(robot[posrobot->y][posrobot->x-1]=='1'){
				return 1;
			}
			break;
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------
void move (Robot *posrobot){ // permet de me déplacer le robot dans le labyrinthe
	switch (posrobot->dir){
		
		case 0:
			posrobot->y--;
			break;
			
		case 1:
			posrobot->x++;
			break;
			
		case 2:
			posrobot->y++;
			break;
			
		case 3:
			posrobot->x--;
			break;
			
		default:
			printf("probléme de direction %d", posrobot->dir);
			break;
	}
}

//-------------------------------------------------------------------------------------------------------------------

 void turn (Robot *posrobot, int rotation){ //permet de changer la direction de mon robot
 
 	if(rotation==0){
 		 if (posrobot->dir==0) posrobot->dir=3;
 		 else posrobot->dir--;
 	}
 	
 	if(rotation==1){
 		 if (posrobot->dir==3) posrobot->dir=0;
 		 else posrobot->dir++;
 	}
 }


//--------------------------------------------------------------------------------------------------------------------

int obstacle (char map[LG_APPART][HT_APPART],Robot *posrobot){// détecte les obstacles en face du robot
	switch (posrobot->dir){
		
		case 0:
			if(map[posrobot->y-1][posrobot->x]=='x') return 0;
			break;
			
		case 1:
			if(map[posrobot->y][posrobot->x+1]=='x') return 0;
			break;
			
		case 2:
			if(map[posrobot->y+1][posrobot->x]=='x') return 0;
			break;
			
		case 3:
			if(map[posrobot->y][posrobot->x-1]=='x') return 0;
			break;
			
		
	}
	return 1;
	}


//--------------------------------------------------------------------------------------------------------------------

int DetecteurSortie(Robot *posrobot,Robot *posfin, int compteur, char robot[LG_APPART][HT_APPART]){// vérifie si la sortie est à côté du robot
	int x=0, y=0;
	x=(posfin->x)-(posrobot->x);
	y=(posfin->y)-(posrobot->y);
	if((x<=1 && x>=-1 && y==0) || (y>=-1 && y<=1 && x==0)){
		//AfficheRobot (robot); Je me servait de cette fonction pour afficher la carte fait par le robot
		printf("Le robot a trouvé la sortie\nIl lui a fallu %d coup pour trouver la sortie\n",compteur);
		return 0;
	}
	else return 1;
}
