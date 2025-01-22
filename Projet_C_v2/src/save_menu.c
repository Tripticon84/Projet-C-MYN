#include "save_menu.h"
#include "game.h"

Save save;

int saveIndex = -1;


#define MAX_BUTTONS 3
static SaveButton buttons[MAX_BUTTONS];
static int selectedButton = 0;
static TTF_Font* font = NULL;

void initSaveMenu() {
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
        "Save 1",
        "Save 2",
        "Save 3"
};

    for (int i = 0; i < MAX_BUTTONS; i++) {
        buttons[i].text = buttonTexts[i];
        buttons[i].isSelected = (i == selectedButton);

        buttons[i].rect.w = 200; // Largeur réduite
        buttons[i].rect.h = 300; // Hauteur augmentée

        int spacing = (792 - (3 * 200)) / 4; // Espacement entre les boutons
        buttons[i].rect.x = spacing + i * (200 + spacing);
        buttons[i].rect.y = (612 - 300) / 2; // Centrer verticalement

        buttons[i].texture = NULL;
    }
}

void handleSaveMenuInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_LEFT:
                    selectedButton--;
                    if (selectedButton<0) selectedButton = MAX_BUTTONS-1;
                    break;
                case SDLK_RIGHT:
                    selectedButton++;
                    if (selectedButton>=MAX_BUTTONS) selectedButton = 0;
                    break;
                case SDLK_RETURN:
                case SDLK_SPACE:
                    if (selectedButton == 0) {
                        // Save 1
                        currentGameState = GAME_STATE_PLAYING;
                        cleanupSaveMenu();
                        saveIndex = 1;
                        initSave(saveIndex);
                    } else if (selectedButton == 1) {
                        // Save 2
                        currentGameState = GAME_STATE_PLAYING;
                        cleanupSaveMenu();
                        saveIndex = 2;
                        initSave(saveIndex);
                    } else if (selectedButton == 2) {
                        // Save 3
                        currentGameState = GAME_STATE_PLAYING;
                        cleanupSaveMenu();
                        saveIndex = 3;
                        initSave(saveIndex);
                    }
                    break;
                case SDLK_ESCAPE:
                    currentGameState = GAME_STATE_MENU;
                    cleanupSaveMenu();
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
                                cleanupSaveMenu();
                                saveIndex = 1;
                                initSave(saveIndex);
                            } else if (i==1) {
                                currentGameState = GAME_STATE_PLAYING;
                                cleanupSaveMenu();
                                saveIndex = 2;
                                initSave(saveIndex);
                            } else if (i==2) {
                                currentGameState = GAME_STATE_PLAYING;
                                cleanupSaveMenu();
                                saveIndex = 3;
                                initSave(saveIndex);
                            }
                        }
                    }
                }
            }
        }
}


void createSave(const int index) {
    // Créer le fichier de sauvegarde
    char filename[256];
    sprintf(filename, "../saves/save%d.sav", index);
    FILE* file = fopen(filename, "wb+");
    if (file == NULL) {
        printf("Erreur création sauvegarde %s\n", filename);
        SDL_Error(500);
    }

    Save newSave = {
        .levelName = "level1",
        .levelPath = "../assets/levels/level1.txt",
        .hearts = 3,
        .score = 0,
        .difficulty = 1
    };

    fwrite(&newSave, sizeof(Save), 1, file);

    fclose(file);
}

void initSave(const int index) {
    // Charger le fichier de sauvegarde
    char filename[256];
    sprintf(filename, "../saves/save%d.sav", index);
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        createSave(saveIndex);
        file = fopen(filename, "rb+");
        if (file == NULL) {
            printf("Erreur ouverture sauvegarde %s\n", filename);
            SDL_Error(500);
        }
    }

    // Lire les données de sauvegarde
    fread(&save, sizeof(Save), 1, file);
    fclose(file);
}

void updateSaveMenu() {
    for (int i=0; i<MAX_BUTTONS; i++){
        buttons[i].isSelected = (i==selectedButton);
    }
}

void updateSave(const int index) {
    // Charger le fichier de sauvegarde
    char filename[256];
    sprintf(filename, "../saves/save%d.sav", index);
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erreur ouverture sauvegarde %s\n", filename);
        SDL_Error(500);
    }

    fwrite(&save, sizeof(Save), 1, file);

    fclose(file);

}

void drawSaveMenu() {
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

void cleanupSaveMenu() {
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
