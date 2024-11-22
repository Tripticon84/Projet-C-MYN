// main.c

#include "game.h"

int main(int argc, char* argv[]) {
    // Initialiser le jeu
    if (initGame() != 0) {
        return 1;
    }

    // Boucle principale du jeu
    gameLoop();

    // Quitter proprement
    cleanupGame();

    return 0;
}