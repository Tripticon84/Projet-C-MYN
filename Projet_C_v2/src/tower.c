#include "tower.h"

int levelCount = 0;
char** tower = NULL;

void createTower() {
    FILE* file = fopen("../tower/tower.txt", "w");
    if (file == NULL) {
        printf("Erreur création du fichier tower\n");
        SDL_Error(500);
    }

    const char* initialTower[] = { "level1.txt", "level2.txt" };

    for (int i = 0; i < 2; i++) {
        fprintf(file, "%s\n", initialTower[i]);
    }
    fclose(file);
}

void initTower() {
    FILE* file = fopen("../tower/tower.txt", "r");
    if (file == NULL) {
        createTower();
        file = fopen("../tower/tower.txt", "r");
        if (file == NULL) {
            printf("Erreur ouverture sauvegarde %s\n", "../tower/tower.txt");
            exit(501);
        }
    }

    // Lire les données de tower
    char levelName[256];
    levelCount = 0;
    tower = NULL; // Initialiser le tableau à NULL

    while (fgets(levelName, 256, file) != NULL) {
        // Supprimer le caractère '\n' à la fin de la chaîne
        levelName[strcspn(levelName, "\n")] = '\0';

        // Redimensionner le tableau principal
        char** temp = realloc(tower, (levelCount + 1) * sizeof(char*));
        if (temp == NULL) {
            perror("Erreur de réallocation mémoire");
            exit(502);
        }
        tower = temp;

        // Allouer de la mémoire pour la nouvelle chaîne et copier les données
        tower[levelCount] = malloc(strlen(levelName) + 1);
        if (tower[levelCount] == NULL) {
            perror("Erreur d'allocation mémoire pour un niveau");
            exit(503);
        }
        strcpy(tower[levelCount], levelName);
        FILE* fichier=fopen("../towertab.txt","a+");
        fprintf(file,"%s\n",tower[levelCount]);
        levelCount++;
        fclose(fichier);
    }
    fclose(file);
}

void addLevelToTower(const char* levelName) {

    if (checkNameTower(levelName) == 1) {
        return;
    }



    // Ajouter le nouveau niveau au fichier
    FILE* file = fopen("../tower/tower.txt", "a");
    if (file == NULL) {
        printf("Erreur ouverture sauvegarde %s\n", "../tower/tower.txt");
        exit(504);
    }

    fprintf(file, "%s\n", levelName);
    fclose(file);

    // Ajouter le niveau au tableau en mémoire
    char** temp = realloc(tower, (levelCount + 1) * sizeof(char*));
    if (temp == NULL) {
        perror("Erreur de réallocation mémoire");
        exit(505);
    }
    tower = temp;

    tower[levelCount] = malloc(strlen(levelName) + 1);
    if (tower[levelCount] == NULL) {
        perror("Erreur d'allocation mémoire pour un niveau");
        exit(506);
    }
    strcpy(tower[levelCount], levelName);
    levelCount++;
}

int checkNameTower(const char* levelName) {
    for (int i = 0; i < levelCount; i++) {
        if (strcmp(levelName, tower[i]) == 0) {
            currentLevel = i;
            return 1;
        }
    }
    return 0;
}


void cleanupTower() {
    for (int i = 0; i < levelCount; i++) {
        free(tower[i]);
    }
    free(tower);
    }



