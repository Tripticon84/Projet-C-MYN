#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/utils.h"
#include <SDL_image.h>
#include "src/player.h"

// Définition des dimensions du sprite
#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 32
#define SPRITE_ROWS 4
#define SPRITE_COLUMNS 4

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow(
            "Jeu de Plateforme",               // Titre de la fenêtre
            SDL_WINDOWPOS_CENTERED,            // Position X
            SDL_WINDOWPOS_CENTERED,            // Position Y
            800,                               // Largeur
            600,                               // Hauteur
            SDL_WINDOW_SHOWN                   // Flags
    );

    if (window == NULL) {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == NULL) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Initialisation de SDL_Image
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Erreur IMG_Init : %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Charger la texture du background
    SDL_Texture *backgroundTexture = loadTexture(renderer, "assets/background.png");
    if (backgroundTexture == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la texture du background : %s\n", SDL_GetError());
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Charger la texture du joueur
    SDL_Texture *playerTexture = loadTexture(renderer, "assets/character.png");
    if (playerTexture == NULL) {
        fprintf(stderr, "Erreur lors du chargement de la texture du joueur : %s\n", SDL_GetError());
        SDL_DestroyTexture(backgroundTexture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return EXIT_FAILURE;
    }

    Player *player = createPlayer(100, 100, SPRITE_WIDTH, SPRITE_HEIGHT, playerTexture);
    if (player == NULL) {
        fprintf(stderr, "Erreur lors de la création du joueur\n");
        SDL_DestroyTexture(playerTexture);
        SDL_DestroyTexture(backgroundTexture);
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Initialisation du temps pour calcul du deltaTime
    Uint32 lastTime = SDL_GetTicks();

    // Variables d'animation
    int frame = 0;
    float animationTimer = 0.0f;
    const float animationSpeed = 0.2f; // Vitesse d'animation (en secondes par frame)

    // Boucle principale
    SDL_bool isRunning = SDL_TRUE;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = SDL_FALSE;
                    break;
                    // Ajoutez d'autres événements ici (clavier, souris)
            }
        }

        // Gestion des entrées
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        handlePlayerInput(player, state);

        // Calcul du deltaTime
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Mise à jour du joueur
        updatePlayer(player, deltaTime);

        // Mise à jour de l'animation
        animationTimer += deltaTime;
        if (animationTimer >= animationSpeed) {
            animationTimer = 0.0f;
            frame = (frame + 1) % SPRITE_COLUMNS; // Passe à la frame suivante
        }

        // Déterminer la ligne de l'animation à utiliser
        int row = 0;
        if (state[SDL_SCANCODE_RIGHT]) {
            row = 1; // Se déplace à droite
        } else if (state[SDL_SCANCODE_LEFT]) {
            row = 3; // Se déplace à gauche
        } else if (state[SDL_SCANCODE_UP]) {
            row = 2; // Saute
        } else {
            row = 0; // Immobile
        }

        // Rendu
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Effacer l'écran en bleu
        SDL_RenderClear(renderer);

        // Afficher le background
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Dessiner le joueur
        SDL_Rect srcRect = {SPRITE_WIDTH * frame, SPRITE_HEIGHT * row, SPRITE_WIDTH, SPRITE_HEIGHT};
        SDL_Rect destRect = {player->x, player->y, player->width, player->height};
        SDL_RenderCopy(renderer, player->texture, &srcRect, &destRect);

        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    destroyPlayer(player);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(backgroundTexture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
