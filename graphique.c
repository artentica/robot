#include "graphique.h"
#include <SDL/SDL.h>


void init(){//Initialisation de la SDL

	if( SDL_Init ( SDL_INIT_VIDEO ) == -1){
		fprintf(stderr, "erreur d'initialisation sur la SDL:\n%s\n", SDL_GetError() );	
		exit(EXIT_FAILURE);	
	}
	//Début de l'audio
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_Music *musique;
	musique = Mix_LoadMUS("musique.mp3");
	Mix_PlayMusic(musique, -1);	
}

//--------------------------------------------------------------------------------------------------------------------

Graph debut(int choix){//Caracteristique de la fenêtre et ça taille ainsi que les images à charger

	init();	
	Graph gr;
	if(choix==2){  //ouvre la fenêtre que si la solution graphique a été demendé
	
	gr.ecran = SDL_SetVideoMode(700, 700, 32, SDL_HWSURFACE || SDL_DOUBLEBUF || SDL_FULLSCREEN );//Taille de la fenêtre
		
		if(gr.ecran == NULL ){
			fprintf(stderr, "on ne peut pas déterminer la taille de la fenêtre: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_WM_SetCaption("Mon gentil robot", NULL);//Nom de ma fenetre
	
	//chargement des images
		gr.fond = SDL_LoadBMP("carrelage.bmp");
		if(gr.fond == NULL ){
			fprintf(stderr, "On ne peut pas ouvrir le fichier carrelage: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		
		
		gr.wall = SDL_LoadBMP("wall.bmp");
		if(gr.wall == NULL ){
			fprintf(stderr, "On ne peut pas ouvrir le fichier wall: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		
		gr.robot = SDL_LoadBMP("robot.bmp");
		if(gr.fond == NULL ){
			fprintf(stderr, "On ne peut pas ouvrir le fichier robot: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		
		gr.sortie = SDL_LoadBMP("sortie.bmp");
		if(gr.fond == NULL ){
			fprintf(stderr, "On ne peut pas ouvrir le fichier robot: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		return gr;
	}
}

//--------------------------------------------------------------------------------------------------------------------

void VerifEvenement(Graph gr){//boucle d'attente d'événement

	SDL_Event event;
	while(SDL_PollEvent( &event) ) {
				
		switch(event.type){
		
			case SDL_KEYDOWN: //Si appuie de touche
				switch(event.key.keysym.sym ){
								
					case SDLK_ESCAPE: //si la touche echap
						SDL_Quit();
						break;	
				}
				break;
	
			case SDL_QUIT:// si la croix de sortie de fenêtre
				SDL_Quit();
				break;	
		}
		
	
	}
	SDL_Flip(gr.ecran);

}

//--------------------------------------------------------------------------------------------------------------------

void AfficheBlock (char car, int i, int j, int deb, Graph gr){
	
	SDL_Rect clip_rect;

	if(deb){//n'affiche les muer et la sortie que une fois
		if(car=='x'){
			clip_rect.y = j*TAILLE_BLOC;
			clip_rect.x = i*TAILLE_BLOC;
			SDL_BlitSurface (gr.wall, NULL,gr.ecran, &clip_rect);
		}
		
		if(car=='S'){
		clip_rect.y = j*TAILLE_BLOC;
		clip_rect.x = i*TAILLE_BLOC;
		SDL_BlitSurface (gr.sortie, NULL, gr.ecran, &clip_rect);
		}
	}
	
	if(car==' '){ //affichage du sol
		clip_rect.y = j*TAILLE_BLOC;
		clip_rect.x = i*TAILLE_BLOC;
		SDL_BlitSurface (gr.fond, NULL, gr.ecran, &clip_rect);
		}
		
	if(car=='R'){ //affichage du robot
		clip_rect.y = j*TAILLE_BLOC;
		clip_rect.x = i*TAILLE_BLOC;
		SDL_BlitSurface (gr.robot, NULL, gr.ecran, &clip_rect);
	}
}

//--------------------------------------------------------------------------------------------------------------------


void texte_fin(Graph gr, int compteur){
 	
	Mix_CloseAudio(); //Fermeture de l'API
	SDL_FillRect(gr.ecran, NULL, SDL_MapRGB(gr.ecran->format, 153,153,221));
	if(TTF_Init()== -1){
	
		puts("erreur ttf");
	}
	TTF_Font *police = TTF_OpenFont("police.ttf", 24);
	SDL_Color couleurNoire = {12, 30, 250};
	SDL_Surface * texte;
	char visible[47];	
	SDL_Rect position;
	position.x = (70);
    position.y = (300);
	sprintf(visible, "Le robot trouve la sortie au bout de %d coups", compteur);
	texte = TTF_RenderText_Blended(police, visible, couleurNoire);
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_Music *musique;
	musique = Mix_LoadMUS("fin.mp3");
	Mix_PlayMusic(musique, -1);	
	
	SDL_BlitSurface(texte, NULL, gr.ecran, &position);
	SDL_Flip(gr.ecran);
	usleep(6000000);
	SDL_FreeSurface(texte);
	TTF_Quit();
	return;
}
