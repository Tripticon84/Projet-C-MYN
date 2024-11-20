// input.c

#include "input.h"

extern int running; // Déclaré dans game.c

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
                case SDLK_ESCAPE:
                    running = 0;
                    break;
            }
        } else if (event->type == SDL_KEYUP) {
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:
                    if (player.velocityX < 0) {
                        player.velocityX = 0;
                    }
                    break;
                case SDLK_RIGHT:
                    if (player.velocityX > 0) {
                        player.velocityX = 0;
                    }
                    break;
            }
        }
    }
}

