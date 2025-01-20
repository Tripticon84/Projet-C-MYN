#ifndef SAVE_MENU_H
#define SAVE_MENU_H

#include <SDL.h>

#include <SDL_ttf.h>


typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    const char* text;
    int isSelected;
} SaveButton;


void initSaveMenu();
void handleSaveMenuInput();
void updateSaveMenu();
void drawSaveMenu();
void cleanupSaveMenu();

void initSave(int saveNumber);
void createSave(int saveNumber);


#endif // SAVE_MENU_H