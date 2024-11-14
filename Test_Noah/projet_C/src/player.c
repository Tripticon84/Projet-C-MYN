#include "player.h"
#include <stdlib.h>

Player *createPlayer(float x, float y, int width, int height, SDL_Texture *texture) {
    Player *player = (Player *)malloc(sizeof(Player));
    if (player == NULL) {
        return NULL;
    }
    player->x = x;
    player->y = y;
    player->vx = 0;
    player->vy = 0;
    player->width = width;
    player->height = height;
    player->texture = texture;
    return player;
}

void destroyPlayer(Player *player) {
    if (player != NULL) {
        // Ne pas détruire la texture ici, elle peut être partagée
        free(player);
    }
}

void handlePlayerInput(Player *player, const Uint8 *state) {
    player->vx = 0;
    if (state[SDL_SCANCODE_LEFT]) {
        player->vx = -100; // Vitesse vers la gauche
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        player->vx = 100; // Vitesse vers la droite
    }
    if (state[SDL_SCANCODE_SPACE]) {
        // Sauter si le joueur est sur le sol
        if (player->vy == 0) {
            player->vy = -200; // Impulsion vers le haut
        }
    }
}

void updatePlayer(Player *player, float deltaTime) {
    // Appliquer la gravité
    player->vy += 981 * deltaTime; // Gravité (981 pixels/s²)

    // Mettre à jour la position
    player->x += player->vx * deltaTime;
    player->y += player->vy * deltaTime;

    // Empêcher le joueur de tomber en dessous du sol (supposons y = 500)
    if (player->y + player->height >= 500) {
        player->y = 500 - player->height;
        player->vy = 0;
    }
}

void renderPlayer(Player *player, SDL_Renderer *renderer) {
    SDL_Rect destRect = {
            (int)player->x,
            (int)player->y,
            player->width,
            player->height
    };
    SDL_RenderCopy(renderer, player->texture, NULL, &destRect);
}
