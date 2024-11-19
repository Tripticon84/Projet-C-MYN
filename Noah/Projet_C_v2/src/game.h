// game.h

#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "level.h"
#include "player.h"
#include "utils.h"

// game.h

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int running;
    // Ajoutez d'autres éléments si nécessaire
} GameState;

// Déclaration des variables globales
extern GameState gameState;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int running;

// Déclarations des fonctions
int initGame();
void gameLoop();
void cleanupGame();

#endif // GAME_H
