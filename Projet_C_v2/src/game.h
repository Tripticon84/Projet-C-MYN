// game.h

#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "level.h"
#include "player.h"
#include "input.h"
#include "utils.h"
#include "menu.h"
#include <SDL_mixer.h>

// Déclaration des variables globales
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int running;

// Déclaration de l'énumération GameState
typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_SAVE_MENU,  // Nouvel état pour le menu des sauvegardes
    GAME_STATE_PLAYING,
    // Ajoutez d'autres états si nécessaire
} GameState;

// Déclaration de la variable globale currentGameState
extern GameState currentGameState;

// Déclaration de la variable globale currentLevel
extern int currentLevel;

// Déclarations des fonctions
int initGame();
void gameLoop();
void cleanupGame();

#endif // GAME_H
