//game.h

#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "level.h"
#include "player.h"
#include "input.h"
#include "utils.h"
#include "menu.h"

//def des états de jeu

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
}GameState;


// Déclaration des variables globales
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int running;
extern GameState currentGameState;
extern

// Déclarations des fonctions
int initGame();
void gameLoop();
void cleanupGame();

#endif // GAME_H