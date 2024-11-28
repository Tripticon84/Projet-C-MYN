// player.c

#include "player.h"

Player player;

// Accès aux données du niveau
extern char levelData[LEVEL_HEIGHT][LEVEL_WIDTH + 2];

// Accès au renderer
extern SDL_Renderer* renderer;

// Déclaration des fonctions internes
static void updatePlayerAnimation();
static void checkTileCollisions(SDL_Rect* rect, int* velocityX, int* velocityY);

void initPlayer() {
    // Charger la texture du joueur
    player.texture = loadTexture("../assets/images/player.png");
    if (!player.texture) {
        printf("Erreur lors du chargement de la texture du joueur.\n");
        return;
    }

    // Initialiser la position et la taille du joueur
    player.rect.x = 36;
    player.rect.y = 576;
    player.rect.w = PLAYER_WIDTH * PLAYER_SCALE;
    player.rect.h = PLAYER_HEIGHT * PLAYER_SCALE;
    player.velocityX = 0;
    player.velocityY = 0;
    player.onGround = 0;

    // Initialiser les variables d'animation
    player.frame = 0;
    player.frameTimer = 0;
    player.frameDuration = PLAYER_FRAME_DURATION;
    player.state = PLAYER_STATE_IDLE;
    player.direction = PLAYER_DIRECTION_RIGHT;
}

void updatePlayer() {
    // Sauvegarder la position précédente
    SDL_Rect previousRect = player.rect;

    // Appliquer la vélocité horizontale
    player.rect.x += player.velocityX;

    // Mettre à jour la direction et l'état du joueur
    if (player.velocityX > 0) {
        player.direction = PLAYER_DIRECTION_RIGHT;
        player.state = PLAYER_STATE_WALKING;
    } else if (player.velocityX < 0) {
        player.direction = PLAYER_DIRECTION_LEFT;
        player.state = PLAYER_STATE_WALKING;
    } else {
        player.state = PLAYER_STATE_IDLE;
    }

    // Vérifier les collisions horizontales
    checkTileCollisions(&player.rect, &player.velocityX, NULL);

    // Appliquer la vélocité verticale
    player.rect.y += player.velocityY;

    // Appliquer la gravité
    if (!player.onGround) {
        player.velocityY += 1; // Gravité
    }

    // Limiter la vitesse de chute
    if (player.velocityY > 10) {
        player.velocityY = 10;
    }

    // Vérifier les collisions verticales
    player.onGround = 0;
    checkTileCollisions(&player.rect, NULL, &player.velocityY);

    // Mettre à jour l'animation
    updatePlayerAnimation();
}

static void updatePlayerAnimation() {
    if (player.state == PLAYER_STATE_WALKING) {
        player.frameTimer += 16; // Supposons que updatePlayer est appelé toutes les 16 ms (~60 FPS)
        if (player.frameTimer >= player.frameDuration) {
            player.frameTimer = 0;
            player.frame = (player.frame + 1) % PLAYER_ANIM_FRAMES;
        }
    } else if (player.state == PLAYER_STATE_IDLE) {
        player.frame = 0;
        player.frameTimer = 0;
    }
}

static void checkTileCollisions(SDL_Rect* rect, int* velocityX, int* velocityY) {
    SDL_Rect tileRect = {0, 0, TILE_WIDTH * RENDER_SCALE, TILE_HEIGHT * RENDER_SCALE};

    for (int y = 0; y < LEVEL_HEIGHT; y++) {
        for (int x = 0; x < LEVEL_WIDTH; x++) {
            char tileChar = levelData[y][x];
            if (tileChar == '#') {
                tileRect.x = x * TILE_WIDTH * RENDER_SCALE;
                tileRect.y = y * TILE_HEIGHT * RENDER_SCALE;

                if (SDL_HasIntersection(rect, &tileRect)) {
                    if (velocityX && *velocityX != 0) {
                        // Collision horizontale
                        if (*velocityX > 0) {
                            rect->x = tileRect.x - rect->w;
                        } else if (*velocityX < 0) {
                            rect->x = tileRect.x + tileRect.w;
                        }
                        *velocityX = 0;
                    }

                    if (velocityY && *velocityY != 0) {
                        // Collision verticale
                        if (*velocityY > 0) {
                            rect->y = tileRect.y - rect->h;
                            player.onGround = 1;
                        } else if (*velocityY < 0) {
                            rect->y = tileRect.y + tileRect.h;
                        }
                        *velocityY = 0;
                    }
                }
            }
        }
    }
}

void drawPlayer() {
    SDL_Rect srcRect;
    srcRect.w = PLAYER_WIDTH;
    srcRect.h = PLAYER_HEIGHT;

    // Calculer la colonne (col) en fonction de la frame
    int col = player.frame;

    // Calculer les coordonnées source en tenant compte de l'espacement
    srcRect.x = col * (PLAYER_WIDTH + PLAYER_SPACE_X);
    srcRect.y = 0; // Une seule ligne

    // Déterminer le flip en fonction de la direction
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (player.direction == PLAYER_DIRECTION_LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_RenderCopyEx(renderer, player.texture, &srcRect, &player.rect, 0, NULL, flip);
}

void cleanupPlayer() {
    if (player.texture) {
        SDL_DestroyTexture(player.texture);
        player.texture = NULL;
    }
}
