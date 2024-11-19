// utils.h

#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

// Fonction pour charger une texture (peut être déplacée ici depuis graphics.h)
SDL_Texture* loadTexture(const char* filepath);

#endif // UTILS_H
