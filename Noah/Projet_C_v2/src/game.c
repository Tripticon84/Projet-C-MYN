// game.c

#include "game.h"

GameState gameState = {0}; // Initialisation

// Variables globales du jeu
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int running = 1;


// Initialise le jeu
int initGame() {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Initialiser SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur lors de l'initialisation de SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Créer la fenêtre
    window = SDL_CreateWindow("Jeu de plateforme",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800, 600,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Créer le renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialiser les autres modules
    initPlayer();
    loadLevel("assets/levels/level1.txt");

    return 0;
}

// Boucle principale du jeu
void gameLoop() {
    SDL_Event event;

    while (running) {
        // Gérer les événements
        handleInput(&event);

        // Mettre à jour le jeu
        updatePlayer();

        // Dessiner le jeu
        SDL_RenderClear(renderer);
        drawLevel();
        drawPlayer();
        SDL_RenderPresent(renderer);

        // Contrôler le framerate
        SDL_Delay(16); // Environ 60 FPS
    }
}

// Nettoie les ressources du jeu
void cleanupGame() {
    // Nettoyer les modules
    cleanupPlayer();
    cleanupLevel();

    // Nettoyer SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
