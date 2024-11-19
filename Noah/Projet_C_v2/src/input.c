// input.c

#include "input.h"
#include "game.h"

void handleInput(SDL_Event* event) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            running = 0;
        } else if (event->type == SDL_KEYDOWN) {
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:
                    player.velocityX = -5;
                    break;
                case SDLK_RIGHT:
                    player.velocityX = 5;
                    break;
                case SDLK_SPACE:
                    if (player.onGround) {
                        player.velocityY = -15; // Saut
                        player.onGround = 0;
                    }
                    break;
                default:
                    break;
            }
        } else if (event->type == SDL_KEYUP) {
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    player.velocityX = 0;
                    break;
                default:
                    break;
            }
        }
    }
}
