// game.c

#include "game.h"

// Variables globales du jeu
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int running = 1;
GameState currentGameState = GAME_STATE_MENU;
int currentLevel = 1; // Niveau actuel

// Déclarer backgroundMusic en variable globale
static Mix_Music* backgroundMusic = NULL;

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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }

    int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(mixFlags) & mixFlags) != mixFlags) {
        printf("Erreur lors de l'initialisation de SDL_mixer (formats): %s\n", Mix_GetError());
        // Pas bloquant, mais attention
    }

    backgroundMusic = Mix_LoadMUS("../assets/music/background.mp3");
    if (!backgroundMusic) {
        printf("Erreur lors du chargement de la musique: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(backgroundMusic, -1);
    }

    // Créer la fenêtre
    window = SDL_CreateWindow("MYN",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              792, 612, // Taille ajustée
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

    // Initialiser le menu
    initMenu();

    return 0;
}

// Boucle principale du jeu
void gameLoop() {
    GameState previousGameState = currentGameState;

    while (running) {
        if (previousGameState != currentGameState) {
            // Changement d'état du jeu
            if (previousGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_PLAYING) {
                // Nettoyer le menu une seule fois lors du passage au jeu
                cleanupMenu();

                // Initialiser les modules nécessaires pour le jeu
                initPlayer();
                loadLevel("../assets/levels/level1.txt");
            }
            previousGameState = currentGameState;
        }

        switch (currentGameState) {
            case GAME_STATE_MENU:
                handleMenuInput();
                updateMenu();

                SDL_RenderClear(renderer);
                drawMenu();
                SDL_RenderPresent(renderer);
                break;

            case GAME_STATE_PLAYING:
                // Gérer les événements
                handleInput();
                // Mettre à jour le jeu
                updatePlayer();

                // Dessiner le jeu
                SDL_RenderClear(renderer);
                drawLevel();
                drawPlayer();
                SDL_RenderPresent(renderer);
                break;

                // Ajoutez d'autres cas si nécessaire
        }

        // Contrôler le framerate
        SDL_Delay(16); // Environ 60 FPS
    }
}

// Nettoie les ressources du jeu
void cleanupGame() {
    // Nettoyer les modules en fonction de l'état du jeu
    if (currentGameState == GAME_STATE_PLAYING) {
        cleanupPlayer();
        cleanupLevel();
    } else if (currentGameState == GAME_STATE_MENU) {
        cleanupMenu();
    }

    // Arrêter et libérer la musique
    Mix_HaltMusic();
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = NULL;
    }

    Mix_CloseAudio();
    Mix_Quit();

    // Nettoyer SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
