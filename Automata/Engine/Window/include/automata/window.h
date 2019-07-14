#ifndef AUTOMATA_WINDOW_H
#define AUTOMATA_WINDOW_H

int automataWindowCreate(int width, int height, const char* title);
int automataWindowDestroy();
int automataWindowShouldClose();
void automataWindowUpdate();
void automataWindowSwapBuffers();

#endif