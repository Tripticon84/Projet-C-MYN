// graphics.c

#include "graphics.h"

SDL_Texture* loadTexture(const char* filepath) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filepath);
    if (!loadedSurface) {
        printf("Erreur lors du chargement de l'image %s: %s\n", filepath, IMG_GetError());
        return NULL;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (!newTexture) {
        printf("Erreur lors de la création de la texture à partir de %s: %s\n", filepath, SDL_GetError());
    }

    return newTexture;
}
