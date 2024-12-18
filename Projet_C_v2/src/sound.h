#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"
#include <stdio.h>



// Fonctions pour initialiser et jouer des sons
int initAudio();
void playMusic(const char *filename);
void playSoundEffect(const char *filename);
void closeAudio();

#endif
