// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "utils.h"

// Structure du joueur
typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
    int velocityX;
    int velocityY;
    int onGround;
} Player;

// Initialise le joueur
void initPlayer();

// Met à jour le joueur
void updatePlayer();

// Dessine le joueur
void drawPlayer();

// Nettoie les ressources du joueur
void cleanupPlayer();

// Accès global au joueur
extern Player player;

#endif // PLAYER_H
