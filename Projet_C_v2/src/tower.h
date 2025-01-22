#ifndef TOWER_H
#define TOWER_H

#include "game.h"

extern char** tower;
extern int levelCount;

void createTower();
void initTower();
void addLevelToTower();
void cleanupTower();
int checkNameTower();

#endif // TOWER_H