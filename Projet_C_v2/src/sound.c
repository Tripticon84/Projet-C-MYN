#include "sound.h"

int initAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur initialisation SDL_mixer : %s\n", Mix_GetError());
        return -1;
    }
    return 0;
}

void playMusic(const char *filename) {
    Mix_Music *music = Mix_LoadMUS("../sounds/son.mp3");
    if (!music) {
        printf("Erreur chargement musique : %s\n", Mix_GetError());
        return;
    }
    Mix_PlayMusic(music, -1); // -1 pour boucle infinie
}


void closeAudio() {
    Mix_CloseAudio();
}

