#ifndef AUTOMATA_WINDOW_H
#define AUTOMATA_WINDOW_H

int automataWindowCreate(int width, int height, const char* title);
void automataWindowDestroy();
int automataWindowShouldClose();
void automataWindowUpdate();
void automataWindowSwapBuffers();
int automataWindowGetWidth();
int automataWindowGetHeight();
void automataWindowSetSize(int width, int height);
void automataWindowSetTitle(const char* title);
void automataWindowCenter();

#endif
