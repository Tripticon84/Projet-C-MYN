// level.c

#include "level.h"

// Exemple simple : une texture pour le sol
SDL_Texture* groundTexture;
SDL_Rect groundRect;

void loadLevel(const char* filename) {
    // Pour simplifier, on charge une texture pour le sol
    groundTexture = loadTexture("assets/images/ground.png");
    if (!groundTexture) {
        printf("Erreur lors du chargement de la texture du sol.\n");
        return;
    }

    // Initialiser la position et la taille du sol
    groundRect.x = 0;
    groundRect.y = 550;
    groundRect.w = 800;
    groundRect.h = 50;
}

void drawLevel() {
    SDL_RenderCopy(renderer, groundTexture, NULL, &groundRect);
}

void cleanupLevel() {
    if (groundTexture) {
        SDL_DestroyTexture(groundTexture);
        groundTexture = NULL;
    }
}
