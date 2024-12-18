#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer.h>

// Initialise le sous-système audio et charge la musique
int initMusic();

// Joue la musique en boucle
void playMusic();

// Coupe ou rétablit la musique selon mute (1 = mute, 0 = unmute)
void setMusicMute(int mute);

// Renvoie 1 si la musique est mute, 0 sinon
int isMusicMuted();

// Nettoie les ressources musicales
void cleanupMusic();

#endif // MUSIC_H
