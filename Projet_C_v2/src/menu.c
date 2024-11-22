// menu.c

#include "menu.h"

#include <math.h>

#include "game.h"
#include <SDL_ttf.h> // Pour le rendu de texte

// Variables pour le menu
#define MAX_BUTTONS 3
Button buttons[MAX_BUTTONS];
int selectedButton = 0;

// Variable pour la police
TTF_Font* font = NULL;

// Initialiser le menu
void initMenu() {
    // Initialiser SDL_ttf
    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation de SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    // Charger la police
    font = TTF_OpenFont("../assets/fonts/PixelOperator8.ttf", 24); // Remplacez par le chemin de votre police
    if (!font) {
        printf("Erreur lors du chargement de la police: %s\n", TTF_GetError());
        return;
    }

    // Initialiser les boutons
    // Exemple avec 3 boutons : Charger Sauvegarde 1, Charger Sauvegarde 2, Quitter
    const char* buttonTexts[MAX_BUTTONS] = {
        "Jouer",
        "Paramètres",
        "Quitter"
    };

    for (int i = 0; i < MAX_BUTTONS; i++) {
        buttons[i].text = buttonTexts[i];
        buttons[i].isSelected = (i == selectedButton) ? 1 : 0;

        // Définir la taille et la position du bouton
        buttons[i].rect.w =200;
        buttons[i].rect.h = 100;
        buttons[i].rect.x = (792 - buttons[i].rect.w) / 2; // Centré horizontalement
        buttons[i].rect.y = 200 + i * 100; // Espacement vertical

        // Optionnel : charger une texture pour le bouton
        // buttons[i].texture = loadTexture("path/to/button_texture.png");
        buttons[i].texture = NULL; // Pas de texture pour l'instant
    }
}

// Gérer les entrées du menu
void handleMenuInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    selectedButton--;
                    if (selectedButton < 0) selectedButton = MAX_BUTTONS - 1;
                    break;
                case SDLK_DOWN:
                    selectedButton++;
                    if (selectedButton >= MAX_BUTTONS) selectedButton = 0;
                    break;
                case SDLK_RETURN:
                case SDLK_SPACE:
                    // Exécuter l'action du bouton sélectionné
                    if (selectedButton == MAX_BUTTONS - 2) {
                        // lance le jeu
                        //currentGameState = GAME_STATE_PLAYING;
                    } else if (selectedButton == MAX_BUTTONS - 1) {
                        // ouvre les paramètres
                    }
                    else {
                        //quitte le jeu
                        running=0;
                    }
                    break;
                default:
                    break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < MAX_BUTTONS; i++) {
                    if (x >= buttons[i].rect.x && x <= buttons[i].rect.x + buttons[i].rect.w &&
                        y >= buttons[i].rect.y && y <= buttons[i].rect.y + buttons[i].rect.h) {
                        // Action du bouton cliqué
                        if (i == MAX_BUTTONS - 2) {
                            // lance le jeu
                            //currentGameState = GAME_STATE_PLAYING;
                        } else if (i == MAX_BUTTONS - 1) {
                            // ouvre les paramètres
                        }
                        else {
                            //quitte le jeu
                            running=0;
                        }
                    }
                }
            }
        }
    }
}

// Mettre à jour le menu (par exemple, changer l'état de sélection)
void updateMenu() {
    // Mettre à jour l'état des boutons
    for (int i = 0; i < MAX_BUTTONS; i++) {
        buttons[i].isSelected = (i == selectedButton) ? 1 : 0;
    }
}

// Dessiner le menu
void drawMenu() {
    // Optionnel : dessiner un arrière-plan pour le menu
    // Vous pouvez charger une texture d'arrière-plan et la dessiner ici

    // Dessiner les boutons
    for (int i = 0; i < MAX_BUTTONS; i++) {
        // Si le bouton a une texture, dessinez-la
        if (buttons[i].texture) {
            SDL_RenderCopy(renderer, buttons[i].texture, NULL, &buttons[i].rect);
        } else {
            // Sinon, dessinez un rectangle
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gris
            if (buttons[i].isSelected) {
                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // Gris clair pour sélection
            }
            SDL_RenderFillRect(renderer, &buttons[i].rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir pour le contour
            SDL_RenderDrawRect(renderer, &buttons[i].rect);
        }

        // Rendre le texte du bouton
        if (font) {
            SDL_Color textColor = {255, 255, 255, 255}; // Blanc
            if (buttons[i].isSelected) {
                textColor.r = 255; textColor.g = 255; textColor.b = 0; // Jaune pour sélection
            }
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttons[i].text, textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    int textW = 0, textH = 0;
                    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
                    SDL_Rect textRect = {
                        buttons[i].rect.x + (buttons[i].rect.w - textW) / 2,
                        buttons[i].rect.y + (buttons[i].rect.h - textH) / 2,
                        textW,
                        textH
                    };
                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }
    }
}

// Nettoyer les ressources du menu
void cleanupMenu() {
    // Nettoyer les textures des boutons si elles existent
    for (int i = 0; i < MAX_BUTTONS; i++) {
        if (buttons[i].texture) {
            SDL_DestroyTexture(buttons[i].texture);
            buttons[i].texture = NULL;
        }
    }

    // Nettoyer la police
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }

    // Quitter SDL_ttf
    TTF_Quit();
}
