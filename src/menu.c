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

enum ETAT {MENU_P,MENU_CPU,MENU_SET};

void close_SDL(SDL_Window *window,SDL_Renderer *renderer,SDL_Texture *texture){
    if(NULL != texture)
        SDL_DestroyTexture(texture);
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

int menu_p(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *tmp,SDL_Texture *texture,SDL_Event event){
    tmp=SDL_LoadBMP("menu.bmp");
int choix;
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);
    Mix_Music *backgroundSound = Mix_LoadMUS("test.mp3");
    Mix_PlayMusic(backgroundSound, -1);
//Gestion du menu/////////////////////////////////////////////////////////////
    choix=0;
    while(choix!=1){
        SDL_WaitEvent(&event);
        switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                Mix_FreeMusic(backgroundSound);
                close_SDL(window,renderer,texture);
                break;
            case SDLK_SPACE:
                choix=1;
                Mix_FreeMusic(backgroundSound);
                return MENU_CPU;
                break;
            default :
                break;
            }
    }
}

int menu_cpu(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *tmp,SDL_Texture *texture,SDL_Event event){
    tmp=SDL_LoadBMP("menu_cpu.bmp");
    int choix;
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);

    choix=0;
    while(choix!=1){
        SDL_WaitEvent(&event);
        switch(event.key.keysym.sym){
            case SDLK_a:
                return MENU_P;
                break;
            case SDLK_1:
                choix=1;
                break;
            case SDLK_2:
                choix=1;
                break;
            case SDLK_3:
                choix=1;
                break;
            default :
                break;
            }
    }
}

void clear_window(SDL_Window *window, SDL_Renderer *renderer,SDL_Texture *texture){
    if(0 != SDL_RenderClear(renderer))//On clear le renderer (on change la couleur)
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        close_SDL(window,renderer,texture);
    }
}

int menu(SDL_Window *window,SDL_Renderer *renderer,SDL_Surface *tmp,SDL_Texture *texture,SDL_Event event){
    int choix;
    while(choix!=1){
        if(menu_p(window,renderer,tmp,texture,event)==MENU_CPU){
        clear_window(window,renderer,texture);
        if(menu_cpu(window,renderer,tmp,texture,event)!=MENU_P)choix=1;
        clear_window(window,renderer,texture);
        }
    }
    return 1;
}

