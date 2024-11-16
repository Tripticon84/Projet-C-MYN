#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

typedef struct {
    float x, y;            // Position
    float vx, vy;          // Vitesse
    int width, height;     // Dimensions
    SDL_Texture *texture;  // Texture
} Player;

Player *createPlayer(float x, float y, int width, int height, SDL_Texture *texture);
void destroyPlayer(Player *player);
void handlePlayerInput(Player *player, const Uint8 *state);
void updatePlayer(Player *player, float deltaTime);
void renderPlayer(Player *player, SDL_Renderer *renderer);

#endif // PLAYER_H
