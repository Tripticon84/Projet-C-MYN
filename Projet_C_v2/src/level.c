// level.c

#include "level.h"

// Matrice pour stocker les données du niveau
char levelData[LEVEL_HEIGHT][LEVEL_WIDTH + 2]; // +2 pour '\n' et '\0'

// Texture pour le tileset
SDL_Texture* tilesetTexture = NULL;

// Structure de correspondance des tuiles
typedef struct {
    char tileChar; // Caractère dans le fichier de niveau
    int tileIndex; // Index de la tuile dans le tileset
} TileMapping;

// Tableau de correspondance des tuiles
TileMapping tileMappings[] = {
        {'#', 5},  // Bloc solide
        {'K', 27}, // Clé
        {'D', 212}, // Porte fermée
        {'O', 232}, // Porte ouverte (nouvelle tuile)
        {'S', 68}, // Pics (nouvelle tuile)
        // Ajoutez d'autres mappings si nécessaire
};

// Nombre de correspondances
#define TILE_MAPPING_COUNT (sizeof(tileMappings) / sizeof(TileMapping))

// Fonction pour obtenir le rectangle source d'une tuile dans le tileset
SDL_Rect getTileSrcRect(char tileChar) {
    SDL_Rect srcRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    int tileIndex = -1;

    // Trouver l'index de la tuile correspondante
    for (int i = 0; i < TILE_MAPPING_COUNT; i++) {
        if (tileMappings[i].tileChar == tileChar) {
            tileIndex = tileMappings[i].tileIndex;
            break;
        }
    }

    if (tileIndex >= 0) {
        int tilesPerRow = 20; // Nombre total de tuiles horizontalement dans le tileset

        int row = tileIndex / tilesPerRow;
        int col = tileIndex % tilesPerRow;

        // Calcul des coordonnées source sans espace entre les tuiles
        srcRect.x = col * TILE_WIDTH;
        srcRect.y = row * TILE_HEIGHT;
    } else {
        // Si tileIndex est négatif, on définit un srcRect vide
        srcRect.w = 0;
        srcRect.h = 0;
    }

    return srcRect;
}

// Fonction pour charger un niveau depuis un fichier
void loadLevel(const char* filename) {
    // Charger la texture du tileset
    tilesetTexture = loadTexture("../assets/images/tilemap.png");
    if (!tilesetTexture) {
        printf("Erreur lors du chargement du tileset.\n");
        return;
    }

    // Ouvrir le fichier du niveau
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier du niveau : %s\n", filename);
        return;
    }

    // Lire le niveau ligne par ligne
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        if (fgets(levelData[i], LEVEL_WIDTH + 2, file) == NULL) {
            printf("Erreur lors de la lecture du niveau.\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
}

// Fonction pour dessiner le niveau
void drawLevel() {
    SDL_Rect destRect;
    destRect.w = TILE_WIDTH * RENDER_SCALE;
    destRect.h = TILE_HEIGHT * RENDER_SCALE;

    for (int y = 0; y < LEVEL_HEIGHT; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            char tileChar = levelData[y][x];

            // Obtenir le rectangle source correspondant à la tuile
            SDL_Rect srcRect = getTileSrcRect(tileChar);

            // Si srcRect.w et srcRect.h sont supérieurs à 0, on dessine la tuile
            if (srcRect.w > 0 && srcRect.h > 0) {
                destRect.x = x * TILE_WIDTH * RENDER_SCALE;
                destRect.y = y * TILE_HEIGHT * RENDER_SCALE;

                SDL_RenderCopy(renderer, tilesetTexture, &srcRect, &destRect);
            }
        }
    }
}

// Fonction pour mettre à jour une tuile du niveau
void setTileAt(int x, int y, char tileChar) {
    if (x >= 0 && x < LEVEL_WIDTH && y >= 0 && y < LEVEL_HEIGHT) {
        levelData[y][x] = tileChar;
    }
}

// Fonction pour nettoyer les ressources du niveau
void cleanupLevel() {
    if (tilesetTexture) {
        SDL_DestroyTexture(tilesetTexture);
        tilesetTexture = NULL;
    }
}
