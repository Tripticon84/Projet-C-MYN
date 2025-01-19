#include "editor.h"


void initEditor(const char* pathToFile) {
    loadLevel(pathToFile);
}

void drawcursor() {
    // Sauvegarde de la couleur de dessin actuelle
    unsigned char r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

    // Définir la couleur du curseur (par exemple, blanc)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Dessiner le rectangle du curseur
    SDL_RenderDrawRect(renderer, &cursorRect);

    // Restaurer la couleur précédente
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void handleEditorInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            // Mettre à jour la position du curseur en fonction de la touche pressée
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (cursorRect.y > 0)  // Empêcher de sortir par le haut
                        cursorRect.y -= TILE_HEIGHT * RENDER_SCALE;
                    break;
                case SDLK_DOWN:
                    if (cursorRect.y < (LEVEL_HEIGHT - 1) * TILE_HEIGHT * RENDER_SCALE)  // Empêcher de sortir par le bas
                        cursorRect.y += TILE_HEIGHT * RENDER_SCALE;
                    break;
                case SDLK_LEFT:
                    if (cursorRect.x > 0)  // Empêcher de sortir à gauche
                        cursorRect.x -= TILE_WIDTH * RENDER_SCALE;
                    break;
                case SDLK_RIGHT:
                    if (cursorRect.x < (LEVEL_WIDTH - 1) * TILE_WIDTH * RENDER_SCALE)  // Empêcher de sortir à droite
                        cursorRect.x += TILE_WIDTH * RENDER_SCALE;
                    break;
                default:
                    break;
            }

            // Redessiner la scène avec la nouvelle position du curseur
            SDL_RenderClear(renderer);  // Efface tout l'écran
            drawEditor();               // Redessine le niveau et le curseur
            SDL_RenderPresent(renderer); // Présente la nouvelle scène
        }
    }
}

void updateEditor() {
    // Mettre à jour la logique de l'éditeur si nécessaire
}

void drawEditor() {
    drawLevel(); // Dessiner le niveau actuel
    drawcursor(); // Dessiner le curseur
}
