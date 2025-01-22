#include "music.h"
#include <stdlib.h>
#include <string.h>

static Mix_Music* backgroundMusic = NULL;
static int musicMuted = 0; // 0 = pas mute, 1 = mute
static char* musicPath = NULL;
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

    if (backgroundMusic == NULL) {
        printf("Erreur chargement musique: %s\n", Mix_GetError());
        return 1;
    }

    FILE* fptr = fopen("../configuration.txt", "r");
    if (fptr == NULL) {
        printf("Erreur ouverture fichier configuration.txt\n");
        return 1;
    }

    char linemusic[256];
    char* value = NULL;
    while (fgets(linemusic, sizeof(linemusic), fptr)) {
        if (strstr(linemusic, "music=") != NULL) {
            value = strchr(linemusic, '=') + 1;
            break;
        }
    }
    fclose(fptr);

    if (value == NULL) {
        printf("Erreur lecture configuration.txt\n");
        return 1;
    }
    if (*value == '0') {
        musicMuted = 1;
    } else {
        musicMuted = 0;
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

int setMusicMute(int mute) {
    if (mute && !musicMuted) {
        // Mute
        previousVolume = Mix_VolumeMusic(-1);
        Mix_VolumeMusic(0);
        musicMuted = 1;

        FILE* fptr = fopen("../configuration.txt", "r+");
        if (fptr == NULL) {
            printf("Erreur ouverture fichier configuration.txt\n");
            return 1;
        }

        long pos;
        char line[256];
        while (fgets(line, sizeof(line), fptr)) {
            char* pos = strstr(line, "music=");
            if (pos != NULL) {
                pos = ftell(fptr) - (long)strlen(line) + (pos - line) + 5;
                fseek(fptr, pos, SEEK_SET);
                fputc('0', fptr);
                break;
            }
        }
        fclose(fptr);
    } else if (!mute && musicMuted) {
        // Unmute
        Mix_VolumeMusic(previousVolume);
        musicMuted = 0;

        FILE* fptr = fopen("../configuration.txt", "r+");
        if (fptr == NULL) {
            printf("Erreur ouverture fichier configuration.txt\n");
            return 1;
        }

        char line[256];
        while (fgets(line, sizeof(line), fptr)) {
            char* pos = strstr(line, "music=");
            if (pos != NULL) {
                pos = ftell(fptr) - (long)strlen(line) + (pos - line) + 5;
                fseek(fptr, pos, SEEK_SET);
                fputc('1', fptr);
                break;
            }
        }
        fclose(fptr);
    }
    return 0;
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
    if (musicPath) {
        free(musicPath);
        musicPath = NULL;
    }
    Mix_CloseAudio();
    Mix_Quit();
}