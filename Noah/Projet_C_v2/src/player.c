// player.c

#include "player.h"

// Instance du joueur
Player player;

void initPlayer() {
    // Charger la texture du joueur
    player.texture = loadTexture("assets/images/player.png");
    if (!player.texture) {
        printf("Erreur lors du chargement de la texture du joueur.\n");
        return;
    }

    // Initialiser la position et la taille du joueur
    player.rect.x = 100;
    player.rect.y = 100;
    player.rect.w = 50;
    player.rect.h = 50;
    player.velocityX = 0;
    player.velocityY = 0;
    player.onGround = 0;
}

void updatePlayer() {
    // Mettre à jour la position du joueur en fonction de la vélocité
    player.rect.x += player.velocityX;
    player.rect.y += player.velocityY;

    // Appliquer la gravité
    if (!player.onGround) {
        player.velocityY += 1; // Gravité simple
    }

    // Gérer les collisions avec le sol (simple exemple)
    if (player.rect.y + player.rect.h >= 550) {
        player.rect.y = 550 - player.rect.h;
        player.velocityY = 0;
        player.onGround = 1;
    }
}

void drawPlayer() {
    SDL_RenderCopy(renderer, player.texture, NULL, &player.rect);
}

void cleanupPlayer() {
    if (player.texture) {
        SDL_DestroyTexture(player.texture);
        player.texture = NULL;
    }
}
