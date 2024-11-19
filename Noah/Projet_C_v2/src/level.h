// level.h

#ifndef LEVEL_H
#define LEVEL_H

#include "graphics.h"
#include "utils.h"

// Dimensions du niveau
#define LEVEL_WIDTH 22
#define LEVEL_HEIGHT 17

// Dimensions des tuiles dans le tileset
#define TILE_WIDTH 18
#define TILE_HEIGHT 18
#define TILE_SPACING 0 // Espace entre les tuiles dans le tileset

// Échelle de rendu (pour agrandir les tuiles à l'écran)
#define RENDER_SCALE 2

// Déclarations des fonctions
void loadLevel(const char* filename);
void drawLevel();
void cleanupLevel();

// Accès global aux données du niveau
extern char levelData[LEVEL_HEIGHT][LEVEL_WIDTH + 2];

#endif // LEVEL_H
