#include "menu.h"
#include "game.h"
#include <SDL_ttf.h>

#define MAX_BUTTONS 4
static Button buttons[MAX_BUTTONS];
static int selectedButton = 0;
static TTF_Font* font = NULL;

void initMenu() {
    if (TTF_Init() == -1) {
        printf("Erreur TTF init: %s\n", TTF_GetError());
        return;
    }

    font = TTF_OpenFont("../assets/fonts/PixelOperator8.ttf", 24);
    if (!font) {
        printf("Erreur police menu: %s\n", TTF_GetError());
        return;
    }

    const char* buttonTexts[MAX_BUTTONS] = {
            "Play",
            "Parameters",
            "Quit",
            "Editor"
    };

    for (int i=0; i<MAX_BUTTONS; i++){
        buttons[i].text = buttonTexts[i];
        buttons[i].isSelected = (i==selectedButton);
        buttons[i].rect.w = 400;
        buttons[i].rect.h = 100;
        buttons[i].rect.x = (792 - 400)/2;
        buttons[i].rect.y = 80 + i*120;
        buttons[i].texture = NULL;
    }
}

void handleMenuInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                    selectedButton--;
                    if (selectedButton<0) selectedButton = MAX_BUTTONS-1;
                    break;
                case SDLK_DOWN:
                    selectedButton++;
                    if (selectedButton>=MAX_BUTTONS) selectedButton = 0;
                    break;
                case SDLK_SPACE:
                    if (selectedButton == 0) {
                        // Play
                        currentGameState = GAME_STATE_PLAYING;
                    } else if (selectedButton == 1) {
                        // Parameters
                        currentGameState = GAME_STATE_SETTINGS;
                        cleanupMenu();
                        initSettingsMenu();
                    } else if (selectedButton == 2) {
                        // Quit
                        SDL_Log("Quitter le jeu");
                        running = 0;
                    }else if (selectedButton==3) {
                        currentGameState=GAME_STATE_EDITOR_LEVEL_NAME;

                    }
                break;
                case SDLK_ESCAPE:
                    running = 0;
                    break;
                default: break;
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x,y;
                SDL_GetMouseState(&x,&y);
                for (int i=0; i<MAX_BUTTONS; i++){
                    if (x>=buttons[i].rect.x && x<=buttons[i].rect.x+buttons[i].rect.w &&
                        y>=buttons[i].rect.y && y<=buttons[i].rect.y+buttons[i].rect.h) {
                        if (i==0) {
                            currentGameState = GAME_STATE_PLAYING;
                        } else if (i==1) {
                            currentGameState = GAME_STATE_SETTINGS;
                            cleanupMenu();
                            initSettingsMenu();
                        } else if (i==2) {
                            running = 0;
                        }else if (i==3) {
                            currentGameState=GAME_STATE_EDITOR_LEVEL_NAME;

                        }
                    }
                }
            }
        }
    }
}

void updateMenu() {
    for (int i=0; i<MAX_BUTTONS; i++){
        buttons[i].isSelected = (i==selectedButton);
    }
}

void drawMenu() {
    for (int i=0; i<MAX_BUTTONS; i++){
        SDL_SetRenderDrawColor(renderer, 100,100,100,255);
        if (buttons[i].isSelected) {
            SDL_SetRenderDrawColor(renderer,150,150,150,255);
        }
        SDL_RenderFillRect(renderer, &buttons[i].rect);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderDrawRect(renderer, &buttons[i].rect);

        if (font) {
            SDL_Color textColor = {255,255,255,255};
            if (buttons[i].isSelected) {
                textColor.r=255;textColor.g=255;textColor.b=0;
            }
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttons[i].text, textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    int textW,textH;
                    SDL_QueryTexture(textTexture,NULL,NULL,&textW,&textH);
                    SDL_Rect textRect = {
                            buttons[i].rect.x+(buttons[i].rect.w - textW)/2,
                            buttons[i].rect.y+(buttons[i].rect.h - textH)/2,
                            textW,
                            textH
                    };
                    SDL_RenderCopy(renderer, textTexture,NULL,&textRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_FreeSurface(textSurface);
            }
        }
    }
}

void cleanupMenu() {
    for (int i=0; i<MAX_BUTTONS; i++){
        if (buttons[i].texture){
            SDL_DestroyTexture(buttons[i].texture);
            buttons[i].texture=NULL;
        }
    }

    if (font) {
        TTF_CloseFont(font);
        font=NULL;
    }
    // Ne pas TTF_Quit() ici si vous l'utilisez ailleurs
}
