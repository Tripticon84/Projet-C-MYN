#include "tower.h"

void createTower() {
    FILE* file = fopen("../saves/tower.lvl", "w+");
    if (file == NULL) {
        printf("Erreur création sauvegarde %s\n", file);
        SDL_Error(500);
    }

    char* tower[] = { "../assets/levels/level1.txt", "../assets/levels/level2.txt"};
    fwrite(tower, sizeof(tower), 1, file);

    fclose(file);
}


void initTower() {

    FILE* file = fopen("../saves/tower.lvl", "rb+");
    if (file == NULL) {
        createTower();
        file = fopen("../saves/tower.lvl", "rb+");
        if (file == NULL) {
            printf("Erreur ouverture sauvegarde %s\n", "../saves/tower.lvl");
            SDL_Error(501);
        }
    }

    // Lire les données de tower
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char** tower = malloc(fileSize);
    fread(tower, fileSize, 1, file);



    fclose(file);
    }
