// menu.h

#ifndef MENU_H
#define MENU_H

#include "graphics.h"
#include "utils.h"
#include <SDL.h>

// Structure pour un bouton
typedef struct {
    SDL_Rect rect;          // Position et taille du bouton
    SDL_Texture* texture;   // Texture du bouton (optionnel)
    const char* text;       // Texte du bouton
    int isSelected;         // Indique si le bouton est sélectionné (pour la navigation clavier)
} Button;

// Initialiser le menu
void initMenu();

// Gérer les entrées du menu
void handleMenuInput();

// Mettre à jour le menu (animations, etc.)
void updateMenu();

// Dessiner le menu
void drawMenu();

// Nettoyer les ressources du menu
void cleanupMenu();

#endif // MENU_H