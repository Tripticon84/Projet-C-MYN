// graphics.h

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

// Variables globales pour la fenêtre et le renderer
extern SDL_Window* window;
extern SDL_Renderer* renderer;

// Charge une texture à partir d'un fichier
SDL_Texture* loadTexture(const char* filepath);

#endif // GRAPHICS_H
