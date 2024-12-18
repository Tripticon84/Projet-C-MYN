#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "graphics.h"
#include "level.h"
#include "player.h"
#include "input.h"
#include "utils.h"
#include "menu.h"
#include "settings_menu.h"
#include "music.h"

// Variables globales
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int running;

// États du jeu
typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_SAVE_MENU,  // si vous en avez besoin
    GAME_STATE_PLAYING,
    GAME_STATE_SETTINGS    // nouvel état pour le menu des paramètres
} GameState;

extern GameState currentGameState;
extern int currentLevel;

// Fonctions globales du jeu
int initGame();
void gameLoop();
void cleanupGame();

#endif // GAME_H
