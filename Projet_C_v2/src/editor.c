#include "editor.h"
static char tiles[]={'.', '#', 'K', 'D', 'S'};
static int lengthTiles = 5;

char cursorX = 0;
char cursorY = 0;

void initEditor(const char* pathToFile) {
    loadLevel(pathToFile);
}

void drawCursor() {
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
                    if (cursorRect.y > 0) { // Empêcher de sortir par le haut
                        cursorRect.y -= TILE_HEIGHT * RENDER_SCALE;
                        cursorY--;
                    }
                    break;
                case SDLK_DOWN:
                    if (cursorRect.y < (LEVEL_HEIGHT - 1) * TILE_HEIGHT * RENDER_SCALE) {  // Empêcher de sortir par le bas
                        cursorRect.y += TILE_HEIGHT * RENDER_SCALE;
                        cursorY++;
                    }
                    break;
                case SDLK_LEFT:
                    if (cursorRect.x > 0) {  // Empêcher de sortir à gauche
                        cursorRect.x -= TILE_WIDTH * RENDER_SCALE;
                        cursorX--;
                    }
                    break;
                case SDLK_RIGHT:
                    if (cursorRect.x < (LEVEL_WIDTH - 1) * TILE_WIDTH * RENDER_SCALE) {  // Empêcher de sortir à droite
                        cursorRect.x += TILE_WIDTH * RENDER_SCALE;
                        cursorX++;
                    }
                    break;
                case SDLK_SPACE:
                    // CHANGER LA TILE À CETTE POSITION;
                    // Par exemple, changer la tuile à la position du curseur en un mur
                    updateTile();
                break;
                case SDLK_DELETE:
                    deleteTile();
                    break;
                case SDLK_ESCAPE:
                    // Retourner au menu principal
                        currentGameState = GAME_STATE_MENU;
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

void saveLevel() {
    FILE* fptr = fopen(pathToFile, "w");
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s pour l'écriture.\n", pathToFile);
        return;
    }

    for (int y = 0; y < LEVEL_HEIGHT; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            fputc(levelData[y][x], fptr);
        }
        fputc('\n', fptr);
    }

    fclose(fptr);
}

void deleteTile() {
    levelData[cursorY][cursorX] = '.';
    setTileAt(cursorX, cursorY, '.');
}

void updateTile() {
    char tuile = levelData[cursorY][cursorX];

    int i;
    switch (tuile) {
        case '.':
            i = 0;
            break;
        case '#':
            i = 1;
            break;
        case 'K':
            i = 2;
            break;
        case 'D':
            i = 3;
            break;
        case 'S':
            i = 4;
            break;
        default:
            i = 0;
            break;
    }

    i = (i + 1) % lengthTiles;


    levelData[cursorY][cursorX] = tiles[i];
    setTileAt(cursorX, cursorY, tiles[i]);

}


void drawEditor() {
    drawLevel(); // Dessiner le niveau actuel
    drawCursor(); // Dessiner le curseur
}

void cleanupEditor() {
    // Nettoyer les ressources de l'éditeur si nécessaire
    cleanupLevel();

}
