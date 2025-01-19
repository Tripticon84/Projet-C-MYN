
#ifndef EDITOR_H
#define EDITOR_H

#include "game.h"


#include <SDL.h>


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
int fileNameAlreadyExist(char* name);

#endif // EDITOR_H
