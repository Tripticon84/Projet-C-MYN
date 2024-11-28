// game.h

#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "level.h"
#include "player.h"
#include "input.h"
#include "utils.h"
#include "menu.h"

// Déclaration des variables globales
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int running;


// Déclaration de l'énumération GameState
typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    // Ajoutez d'autres états si nécessaire
} GameState;

// Déclaration de la variable globale currentGameState
extern GameState currentGameState;

// Déclarations des fonctions
int initGame();
void gameLoop();
void cleanupGame();

#endif // GAME_H