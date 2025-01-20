#include "editorLevelName.h"
#include <SDL_ttf.h>
#include <stdio.h>



static TTF_Font* font = NULL;
static const char* askName ="Choose a level name";
static Square square;

static SDL_Rect inputRect;
static char inputText[256] = "";
static int inputTextLength = 0;


void initEditorLevelName() {
    pathToFile = NULL; // Réinitialiser pathToFile

    if (TTF_Init() == -1) {
        printf("Erreur TTF init: %s\n", TTF_GetError());
        return;
    }

    font = TTF_OpenFont("../assets/fonts/PixelOperator8.ttf", 24);
    if (!font) {
        printf("Erreur police menu: %s\n", TTF_GetError());
    }
    square.text = askName;
    square.rect.w = 400;
    square.rect.h = 100;
    square.rect.x = (792 - 400)/2;
    square.rect.y = 80 + 120;
    square.texture = NULL;

    // Initialisez le champ de saisie
    inputRect.w = 400;
    inputRect.h = 50;
    inputRect.x = (792 - 400)/2;
    inputRect.y = square.rect.y + square.rect.h + 20;

    SDL_StartTextInput();

}

void handleEditorLevelNameInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_BACKSPACE && inputTextLength > 0) {
                inputText[--inputTextLength] = '\0';
            } else if (event.key.keysym.sym == SDLK_RETURN) {

                pathToFile = initFile(inputText);
                currentGameState = GAME_STATE_EDITOR;
            }
        } else if (event.type == SDL_TEXTINPUT) {
            if (inputTextLength < sizeof(inputText) - 1) {
                strcat(inputText, event.text.text);
                inputTextLength += strlen(event.text.text);
            }
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            currentGameState = GAME_STATE_MENU;
        }
    }
}

char* initFile(char* name) {
    static char path[300];

    strcpy(path, "../assets/levels/");
    strcat(path, strcat(name, ".txt"));

    FILE* file = fopen(path, "r+");
    if (file == NULL) {
        file = fopen(path, "w");
        if (file == NULL) {
            fprintf(stderr, "Erreur lors de la création du fichier\n");
            exit(500);
        }
        for (int y = 0; y < LEVEL_HEIGHT; y++) {
            for (int x = 0; x < LEVEL_WIDTH; x++) {
                if ( y == LEVEL_HEIGHT - 1 || x == 0 || x == LEVEL_WIDTH - 1) {
                    fputc('#', file);
                } else {
                    fputc('.', file);
                }
            }
            fputc('\n', file);
        }

    }
    fclose(file);
    return path;
}

void drawEditorLevelName(){
    SDL_SetRenderDrawColor(renderer, 100,100,100,255);
    SDL_RenderFillRect(renderer, &square.rect);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawRect(renderer, &square.rect);

    SDL_Color textColor = {255,255,255,255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, square.text, textColor);
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture) {
            int textW,textH;
            SDL_QueryTexture(textTexture,NULL,NULL,&textW,&textH);
            SDL_Rect textRect = {
                square.rect.x+(square.rect.w - textW)/2,
                square.rect.y+(square.rect.h - textH)/2,
                textW,
                textH
            };
            SDL_RenderCopy(renderer, textTexture,NULL,&textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }

    // Dessinez le champ de saisie
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderFillRect(renderer, &inputRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &inputRect);

    // Dessinez le texte saisi
    textSurface = TTF_RenderText_Solid(font, inputText, textColor);
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture) {
            int textW, textH;
            SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
            SDL_Rect textRect = {
                inputRect.x + 5,
                inputRect.y + (inputRect.h - textH) / 2,
                textW,
                textH
            };
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }

}

void cleanupEditorLevelName() {
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }

    SDL_StopTextInput();
    inputText[0] = '\0';
}

