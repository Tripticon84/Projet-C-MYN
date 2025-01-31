// input.c

#include "input.h"

extern int running; // Déclaré dans game.c

void handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            currentGameState=GAME_STATE_MENU;
        }
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // Réinitialiser la vélocité horizontale
    player.velocityX = 0;

    // Gérer les mouvements gauche/droite
    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A] ) {
        player.velocityX = -5;
        player.direction = PLAYER_DIRECTION_LEFT;
        player.state = PLAYER_STATE_WALKING;
    } else if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) {
        player.velocityX = 5;
        player.direction = PLAYER_DIRECTION_RIGHT;
        player.state = PLAYER_STATE_WALKING;
    } else {
        player.state = PLAYER_STATE_IDLE;
    }

    // Gérer le saut
    if (keystate[SDL_SCANCODE_SPACE] || keystate[SDL_SCANCODE_W]) {
        if (player.onGround) {
            player.velocityY = -15; // Saut
            player.onGround = 0;
        }
    }
}
