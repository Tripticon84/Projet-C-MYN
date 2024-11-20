// game.h

#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "level.h"
#include "player.h"
#include "input.h"
#include "utils.h"

// Déclaration des variables globales
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int running;

// Déclarations des fonctions
int initGame();
void gameLoop();
void cleanupGame();

#endif // GAME_H
