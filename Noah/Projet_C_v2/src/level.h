// level.h

#ifndef LEVEL_H
#define LEVEL_H

#include "graphics.h"
#include "utils.h"

// Charge un niveau depuis un fichier
void loadLevel(const char* filename);

// Dessine le niveau
void drawLevel();

// Nettoie les ressources du niveau
void cleanupLevel();

#endif // LEVEL_H
