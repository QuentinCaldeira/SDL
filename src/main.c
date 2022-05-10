// std
#include <stdio.h>

// opengl
#include <GL/glew.h>

// sdl
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "menu.h"

#include <time.h>
#include "ensemble_liste.h"

//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


SDL_AudioSpec spec;




int setWindowColor(SDL_Renderer *renderer, SDL_Color color){
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g,color.b, color.a) < 0)return -1;
    if(SDL_RenderClear(renderer) < 0)return -1;
    return 0;
}

void print_card(SDL_Renderer *renderer, int posx, int posy, int card, int couleur,float ratioL, float ratioH, float zoom){
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    //SDL_RenderClear( renderer );
    SDL_Rect srcrect = { card*137, 205*couleur, 137, 205 };
    SDL_Rect dstrect = {posx, posy, 137*ratioL*zoom, 205*ratioH*zoom};
    tmp=SDL_LoadBMP("uno_cards.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    SDL_RenderCopy(renderer,texture,&srcrect,&dstrect);
    SDL_RenderPresent(renderer);
}

void affichage_carte(int taille,SDL_Renderer *renderer, float ratioL, float ratioH, ENSEMBLE joueur, float zoom){
    int i;
    CARTE *c;
    c=joueur.elements;
    int couleur;
        for(i=0;i<taille;i++){ 
                switch(c->couleur){
                case 'R' :
                    couleur=0;
                    break;
                case 'J' :
                    couleur=1;
                    break;
                case 'V' :
                    couleur=2;
                    break;
                case 'B' :
                    couleur=3;
                    break;
                }
            if(taille<35){
            zoom=1;
            print_card(renderer,100*ratioL+(137*zoom*(i-(17*(i/17)))*ratioL),(1440-100)*ratioH-(205*zoom*ratioH*((i/17)+1)),c->valeur,couleur,ratioL,ratioH,zoom);
            }
            else{
            zoom=0.7;
            print_card(renderer,100*ratioL+(137*zoom*(i-(24*(i/24)))*ratioL),(1440-100)*ratioH-(205*zoom*ratioH*((i/24)+1)),c->valeur,couleur,ratioL,ratioH,zoom);
            } 
            c=c->suivant;     
        }
}

int collision_carte(int taille, float ratioL, float ratioH,float zoom){
    SDL_bool quit = SDL_FALSE;
    SDL_Event event;
    int PosMouseX,PosMouseY,i,carteclick;
    while(!quit){
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT)quit = SDL_TRUE;
        else if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT)SDL_GetMouseState(&PosMouseX,&PosMouseY);
            if(taille<35){
                for(i=0;i<=taille/17;i++){
                    zoom=1;
                    if(((PosMouseY)>(1340*ratioH-(205*(i+1))*ratioH))&&(PosMouseY<(1340*ratioH-(205*i)*ratioH))){
                    carteclick=(PosMouseX-(100*ratioL))/(137*ratioL);
                        if(carteclick+(17*i)<=taille){
                        printf("\n\nLa carte est : %d\n\n",carteclick+(17*i));   
                        quit=SDL_TRUE;
                        }    
                    }   
                }
            }
            else{
                for(i=0;i<=taille/24;i++){
                    zoom=0.7;
                    if(((PosMouseY)>(1340*ratioH-(205*zoom*(i+1))*ratioH))&&(PosMouseY<(1340*ratioH-(205*zoom*i)*ratioH))){
                        carteclick=(PosMouseX-(100*ratioL))/(137*ratioL*zoom);
                        if(carteclick+(24*i)<=taille){
                            printf("\n\nLa carte est : %d\n\n",carteclick+(24*i)); 
                            quit=SDL_TRUE;
                        }      
                    }   
                }
            }
        } 
    }
    return 1;
}





int main(int argc, char *argv[])
{
//Initialisation de variables SDL////////////////////////////
srand(time(NULL));
    SDL_Window *window = NULL;//Initialisation de la fenetre
    SDL_Renderer *renderer = NULL;
    SDL_Surface *tmp = NULL; 
    SDL_Texture *texture = NULL;
    SDL_Event event;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    float ratioL,ratioH;
    int SizeWindowH,SizeWindowL;
    int statut = EXIT_FAILURE;
    float zoom=1;


    ENSEMBLE* Paquet=init_paquet();
	
	/*Initialisation et creation des mains des joueurs */
	ENSEMBLE* J1=init_ensemble();
	ENSEMBLE* J2=init_ensemble();
	ENSEMBLE* J3=init_ensemble();
	ENSEMBLE* J4=init_ensemble();

    distribution_random(Paquet,J1, 7,rand());
	distribution_random(Paquet,J2, 7,rand());
	distribution_random(Paquet,J3, 7,rand());
	distribution_random(Paquet,J4, 7,rand());

        //Initialisation de la fenetre///////////////////////////////////////////
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
        
    }
    if(0 != SDL_CreateWindowAndRenderer(2560, 1440, SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_OPENGL, &window, &renderer)){//Creer une fenetre et un renderer{
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }
    SDL_SetWindowTitle(window,"Projet Co UNO");
    if(0 != SDL_SetRenderDrawColor(renderer,255,0,0,255)){//Choix de la couleur
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }
/////////////////////////////////////////////////////////////////////////

    SDL_GetWindowSize(window,&SizeWindowL,&SizeWindowH);
    ratioL=(float)SizeWindowL/2560;//Calcul ratio d'affichage largeur
    ratioH=(float)SizeWindowH/1440;//Calcul ratio hauteur

    while(!menu(window,renderer,tmp,texture,event));//Tant qu'on est dans le menu

    SDL_Color blue = {0, 0, 255, 255};
    SDL_RenderClear(renderer);
    setWindowColor(renderer, blue);//Fond du jeu

    affichage_carte(J1->cardinal,renderer,ratioL,ratioH,*J1,zoom);
    collision_carte(J1->cardinal, ratioL, ratioH,zoom);
    SDL_Delay(1000);    

Quit:
    if(NULL != texture)
        SDL_DestroyTexture(texture);
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}


