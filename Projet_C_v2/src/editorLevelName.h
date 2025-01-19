
#ifndef EDITOR_LEVEL_NAME_H
#define EDITOR_LEVEL_NAME_H

#include "game.h"


typedef struct {
    SDL_Rect rect;          // Position et taille du bouton
    SDL_Texture* texture;   // Texture du bouton (optionnel)
    const char* text;       // Texte du bouton
    int isSelected;         // Indique si le bouton est sélectionné (pour la navigation clavier)
} Square;

void initEditorLevelName();
void handleEditorLevelNameInput();
void drawEditorLevelName();
void cleanupEditorLevelName();
char* initFile(char* name);

#endif // EDITOR_LEVEL_NAME_H
