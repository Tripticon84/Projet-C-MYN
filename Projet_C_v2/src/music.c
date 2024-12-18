#include "music.h"
#include <stdio.h>

static Mix_Music* backgroundMusic = NULL;
static int musicMuted = 0; // 0 = pas mute, 1 = mute
static int previousVolume = MIX_MAX_VOLUME; // volume avant mute

int initMusic() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur init SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }

    int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(mixFlags) & mixFlags) != mixFlags) {
        printf("Erreur init SDL_mixer (formats): %s\n", Mix_GetError());
        // Non bloquant, on peut continuer
    }

    backgroundMusic = Mix_LoadMUS("../assets/music/background.mp3");
    if (!backgroundMusic) {
        printf("Erreur chargement musique: %s\n", Mix_GetError());
    }

    return 0;
}

void playMusic() {
    if (backgroundMusic) {
        Mix_PlayMusic(backgroundMusic, -1);
        if (musicMuted) {
            Mix_VolumeMusic(0);
        } else {
            Mix_VolumeMusic(previousVolume);
        }
    }
}

void setMusicMute(int mute) {
    if (mute && !musicMuted) {
        // Mute
        previousVolume = Mix_VolumeMusic(-1);
        Mix_VolumeMusic(0);
        musicMuted = 1;
    } else if (!mute && musicMuted) {
        // Unmute
        Mix_VolumeMusic(previousVolume);
        musicMuted = 0;
    }
}

int isMusicMuted() {
    return musicMuted;
}

void cleanupMusic() {
    Mix_HaltMusic();
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = NULL;
    }
    Mix_CloseAudio();
    Mix_Quit();
}
