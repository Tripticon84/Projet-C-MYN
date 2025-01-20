#include "game.h"


// Variables globales du jeu
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int running = 1;
GameState currentGameState = GAME_STATE_MENU;
int currentLevel = 1; // Niveau actuel

char* pathToFile = NULL;

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

    // Initialiser la fenêtre
    window = SDL_CreateWindow("MYN",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              792, 612,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur creation fenetre: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialiser le renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur creation renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialiser la musique
    if (initMusic() != 0) {
        // Si erreur, on peut continuer sans musique, ou quitter
        // Ici on continue, mais la musique ne sera pas jouée
    } else {
        playMusic();
    }

    // Initialiser le menu principal
    initMenu();

    return 0;
}

void gameLoop() {
    GameState previousGameState = currentGameState;

    while (running) {
        if (previousGameState != currentGameState) {
            // Changement d'état du jeu
            if (previousGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_PLAYING) {
                // On vient de quitter le menu pour jouer
                //cleanupMenu(); // On nettoie le menu
                //initPlayer();
                //loadLevel("../assets/levels/level1.txt");
            } else if (previousGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_SETTINGS) {
                // On ouvre le menu des paramètres depuis le menu principal
                cleanupMenu();
                initSettingsMenu();
            } else if (previousGameState == GAME_STATE_SETTINGS && currentGameState == GAME_STATE_MENU) {
                // On retourne au menu principal depuis les paramètres
                cleanupSettingsMenu();
                initMenu();
            } else if (previousGameState == GAME_STATE_PLAYING && currentGameState == GAME_STATE_MENU) {
                // Si on retourne au menu principal depuis le jeu (pas implémenté ici, juste un exemple)
                cleanupPlayer();
                cleanupLevel();
                initMenu();
            } else if (previousGameState == GAME_STATE_MENU && currentGameState == GAME_STATE_EDITOR_LEVEL_NAME) {
                // On ouvre l'éditeur de niveau depuis le menu principal
                cleanupMenu();
                initEditorLevelName();
            } else if (previousGameState == GAME_STATE_EDITOR_LEVEL_NAME && currentGameState == GAME_STATE_MENU) {
                // Si on retourne au menu principal depuis le jeu (pas implémenté ici, juste un exemple)
                cleanupEditorLevelName();
                initMenu();
            } else if (previousGameState == GAME_STATE_EDITOR_LEVEL_NAME && currentGameState == GAME_STATE_EDITOR) {
                cleanupEditorLevelName();
                initEditor(pathToFile);
            } else if (previousGameState == GAME_STATE_EDITOR && currentGameState == GAME_STATE_MENU) {
                saveLevel();
                cleanupEditor();
                initMenu();
            } else if(previousGameState==GAME_STATE_MENU && currentGameState==GAME_STATE_SAVE_MENU) {
                cleanupMenu();
                initSaveMenu();
            } else if (previousGameState==GAME_STATE_SAVE_MENU && currentGameState==GAME_STATE_MENU) {
                cleanupSaveMenu();
                initMenu();
            } else if (previousGameState==GAME_STATE_SAVE_MENU && currentGameState==GAME_STATE_PLAYING) {
                cleanupSaveMenu();
                initPlayer();
                loadLevel(save.levelPath);
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

            case GAME_STATE_SETTINGS:
                handleSettingsMenuInput();
                updateSettingsMenu();

                SDL_RenderClear(renderer);
                drawSettingsMenu();
                SDL_RenderPresent(renderer);
                break;

            case GAME_STATE_PLAYING:
                handleInput();
                updatePlayer();

                SDL_RenderClear(renderer);
                drawLevel();
                drawPlayer();
                SDL_RenderPresent(renderer);
                break;

            case GAME_STATE_EDITOR_LEVEL_NAME:
                handleEditorLevelNameInput();

                SDL_RenderClear(renderer);
                drawEditorLevelName();
                SDL_RenderPresent(renderer);
                break;
            case GAME_STATE_EDITOR:
                handleEditorInput();

                SDL_RenderClear(renderer);
                drawEditor();
                SDL_RenderPresent(renderer);
                break;
            case GAME_STATE_SAVE_MENU:
                handleSaveMenuInput();
                updateSaveMenu();

                SDL_RenderClear(renderer);
                drawSaveMenu();
                SDL_RenderPresent(renderer);
                break;
            default:
                break;
        }

        SDL_Delay(16); // ~60 FPS
    }
}

void cleanupGame() {
    // Nettoyer selon l'état
    if (currentGameState == GAME_STATE_PLAYING) {
        cleanupPlayer();
        cleanupLevel();
    } else if (currentGameState == GAME_STATE_MENU) {
        cleanupMenu();
    } else if (currentGameState == GAME_STATE_SETTINGS) {
        cleanupSettingsMenu();
    }


    cleanupMusic();

    // Nettoyer SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}