
#ifndef EDITOR_H
#define EDITOR_H

#include "level.h"


void initEditor(const char* pathToFile);
void handleEditorInput();
void drawEditor();
void drawcursor();
void cleanupEditor();
void updateEditor();
static SDL_Rect cursorRect = {0, 0, TILE_WIDTH * RENDER_SCALE, TILE_HEIGHT * RENDER_SCALE};

#endif // EDITOR_H
