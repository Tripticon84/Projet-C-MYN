#include "settings_menu.h"
#include "graphics.h"
#include "game.h"
#include "music.h"
#include <SDL_ttf.h>

static TTF_Font* settingsFont = NULL;
static int selectedOption = 0;

#define SETTINGS_MAX_OPTIONS 2
static const char* options[SETTINGS_MAX_OPTIONS] = {
        "Toggle Music",
        "Back"
};

void initSettingsMenu() {
    if (!TTF_WasInit()) {
        TTF_Init();
    }
    settingsFont = TTF_OpenFont("../assets/fonts/PixelOperator8.ttf", 24);
    if (!settingsFont) {
        printf("Erreur chargement police param: %s\n", TTF_GetError());
    }
}

void handleSettingsMenuInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    selectedOption--;
                    if (selectedOption < 0) selectedOption = SETTINGS_MAX_OPTIONS - 1;
                    break;
                case SDLK_DOWN:
                    selectedOption++;
                    if (selectedOption >= SETTINGS_MAX_OPTIONS) selectedOption = 0;
                    break;
                case SDLK_RETURN:
                case SDLK_SPACE:
                    if (selectedOption == 0) {
                        // Toggle Music
                        setMusicMute(!isMusicMuted());
                    } else if (selectedOption == 1) {
                        // Back au menu principal
                        currentGameState = GAME_STATE_MENU;
                        cleanupSettingsMenu();
                        initMenu();
                    }
                    break;
                case SDLK_ESCAPE:
                    currentGameState = GAME_STATE_MENU;
                    cleanupSettingsMenu();
                    initMenu();
                    break;
                default:
                    break;
            }
        }
    }
}

void updateSettingsMenu() {
    // Màj éventuelle de l'UI ou animations
}

void drawSettingsMenu() {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Afficher l'état de la musique
    const char* musicState = isMusicMuted() ? "Music: Muted" : "Music: Unmuted";
    SDL_Color infoColor = {200, 200, 200, 255};
    if (settingsFont) {
        SDL_Surface* infoSurface = TTF_RenderText_Solid(settingsFont, musicState, infoColor);
        if (infoSurface) {
            SDL_Texture* infoTexture = SDL_CreateTextureFromSurface(renderer, infoSurface);
            if (infoTexture) {
                int infoW, infoH;
                SDL_QueryTexture(infoTexture, NULL, NULL, &infoW, &infoH);
                SDL_Rect infoRect = {(792 - infoW)/2, 100, infoW, infoH};
                SDL_RenderCopy(renderer, infoTexture, NULL, &infoRect);
                SDL_DestroyTexture(infoTexture);
            }
            SDL_FreeSurface(infoSurface);
        }
    }

    for (int i = 0; i < SETTINGS_MAX_OPTIONS; i++) {
        SDL_Color textColor = {255,255,255,255};
        if (i == selectedOption) {
            textColor.r = 255; textColor.g = 255; textColor.b = 0;
        }

        if (settingsFont) {
            SDL_Surface* textSurface = TTF_RenderText_Solid(settingsFont, options[i], textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    int textW, textH;
                    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
                    SDL_Rect dstRect = {
                            (792 - textW)/2,
                            200 + i*100,
                            textW,
                            textH
                    };
                    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }
    }
}

void cleanupSettingsMenu() {
    if (settingsFont) {
        TTF_CloseFont(settingsFont);
        settingsFont = NULL;
    }
}
