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
    const char* buttonTexts[MAX_BUTTONS] = {
        "Play",
        "Parameters",
        "Quit"
    };

    for (int i = 0; i < MAX_BUTTONS; i++) {
        buttons[i].text = buttonTexts[i];
        buttons[i].isSelected = (i == selectedButton) ? 1 : 0;

        // Définir la taille et la position du bouton
        buttons[i].rect.w = 400;
        buttons[i].rect.h = 100;
        buttons[i].rect.x = (792 - buttons[i].rect.w) / 2; // Centré horizontalement
        buttons[i].rect.y = 150 + i * 120; // Espacement vertical ajusté
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
                    if (selectedButton == 0) {
                        // Lancer le jeu
                        currentGameState = GAME_STATE_PLAYING;
                    } else if (selectedButton == 1) {
                        // Ouvrir les paramètres
                        // À implémenter
                    } else if (selectedButton == 2) {
                        // Quitter le jeu
                        SDL_Log("Quitter le jeu");
                        running = 0;
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
                        if (i == 0) {
                            // Lancer le jeu
                            currentGameState = GAME_STATE_PLAYING;
                        } else if (i == 1) {
                            // Ouvrir les paramètres
                            // À implémenter
                        } else if (i == 2) {
                            // Quitter le jeu
                            SDL_Log("Quitter le jeu");
                            running = 0;
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
    // Dessiner les boutons
    for (int i = 0; i < MAX_BUTTONS; i++) {
        // Dessiner le fond du bouton
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gris
        if (buttons[i].isSelected) {
            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // Gris clair pour la sélection
        }
        SDL_RenderFillRect(renderer, &buttons[i].rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir pour le contour
        SDL_RenderDrawRect(renderer, &buttons[i].rect);

        // Rendre le texte du bouton
        if (font) {
            SDL_Color textColor = {255, 255, 255, 255}; // Blanc
            if (buttons[i].isSelected) {
                textColor.r = 255; textColor.g = 255; textColor.b = 0; // Jaune pour la sélection
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