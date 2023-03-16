#include "../../include/init_supr_sdl.h"

int creation_pack(pack_t * fenetre, char * titre){
    /**
     * \brief Création de la fenêtre
     */
    fenetre->fenetre = SDL_CreateWindow(titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_RESIZABLE);
    /**
     * \brief Gestion d'erreur de la fenêtre
     */
    if(fenetre->fenetre == NULL){ 
        printf("Erreur de création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /** 
     * \brief création du renedrer
     */
    fenetre->renderer = SDL_CreateRenderer(fenetre->fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    /**
     * \brief gestion d'erreur du renderer
     */
    if(fenetre->renderer == NULL){
        printf("Erreur de création du renderer : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /**
     * \brief creation de la police
     */
    fenetre->police = TTF_OpenFont("./ressources/arial.ttf", 20);
    /**
     * \brief gestion d'erreur de la police
     */
    if(fenetre->police == NULL){
        printf("Erreur de création de la police : %s", TTF_GetError());
        SDL_Quit();
        return 1 ;
    }
    return 0;


}

int intilalisation_sdl(){
    /**
     * \brief Initialisation de la SDL avecc gestion d'erreur
     * 
     */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
        printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }
    /**
     * \brief Initialisation de SDL_ttf avec gestion d'erreur
     */
    if(TTF_Init() < 0){
        printf("Erreur d'initialisation de SDL_ttf : %s", TTF_GetError());
        SDL_Quit();
        return 1 ;
    }
}


void supression_pack(pack_t * fenetre){
    /**
     * \brief Supression de la fenêtre
     */
    SDL_DestroyWindow(fenetre->fenetre);
    /**
     * \brief Supression du renderer
     */
    SDL_DestroyRenderer(fenetre->renderer);
    /**
     * \brief Supression de la police
     */
    TTF_CloseFont(fenetre->police);
}

void supression_sdl(){
    /**
     * \brief Quitte SDL_ttf
     */
    TTF_Quit();
    /**
     * \brief Quitte la SDL
     */
    SDL_Quit();
}




int load_bitmap(const char *path, texture_t *texture, pack_t * fenettre){
    SDL_Surface * fond = NULL;
    /**
     * \brief load de la bitmap
     */
    fond = SDL_LoadBMP(path);
    /**
     * \brief gestion d'erreur du load
     */
    if(fond == NULL){
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /**
     * \brief création de la texture
     */
    texture->texture = SDL_CreateTextureFromSurface(fenettre->renderer, fond);
    /**
     * \brief gestion d'erreur de la texture
     */
    if(texture->texture == NULL){
        printf("Erreur de création de la texture : %s", SDL_GetError());
        SDL_Quit();
        return 1 ;
    }

    /**
     * \brief libération de la surface
     */
    SDL_FreeSurface(fond);
    return 0;
}

void supression_texture(texture_t * texture){
    /**
     * \brief Supression de la texture
     */
    SDL_DestroyTexture(texture->texture);
    if(texture->precedent != NULL){
        texture->precedent->suivant = texture->suivant;
    }
    if(texture->suivant != NULL){
        texture->suivant->precedent = texture->precedent;
    }
    free(texture);
    texture = NULL;
}

void supression_texture_liste(texture_t * texture){
    /**
     * \brief Supression de la texture
     */
    if(texture->suivant != NULL){
        supression_texture_liste(texture->suivant);
    }
    supression_texture(texture);
}