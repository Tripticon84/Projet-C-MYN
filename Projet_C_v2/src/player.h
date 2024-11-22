// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "utils.h"
#include "level.h"

// Dimensions du joueur
#define PLAYER_WIDTH 13
#define PLAYER_HEIGHT 19
#define PLAYER_SCALE 2

// Ajoutez ces définitions pour l'espacement entre les frame du player
#define PLAYER_SPACE_X 19 // Espacement horizontal entre les les frame de player en pixels

// Constantes pour les animations
#define PLAYER_ANIM_FRAMES 4 // Nombre de frames par animation
#define PLAYER_FRAME_DURATION 100 // Durée de chaque frame en millisecondes

// États du joueur
typedef enum {
    PLAYER_STATE_IDLE,
    PLAYER_STATE_WALKING,
    // Ajoutez d'autres états si nécessaire
} PlayerState;

// Directions du joueur
typedef enum {
    PLAYER_DIRECTION_RIGHT,
    PLAYER_DIRECTION_LEFT,
} PlayerDirection;

// Structure du joueur
typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
    int velocityX;
    int velocityY;
    int onGround;
    // Variables pour l'animation
    int frame;
    int frameTimer;
    int frameDuration;
    PlayerState state;
    PlayerDirection direction;
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