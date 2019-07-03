#ifndef AUTOMATA_WINDOW_H
#define AUTOMATA_WINDOW_H

void automataWindowCreate(int width, int height, const char* title);
void automataWindowDestroy();
int automataWindowShouldClose();
void automataWindowUpdate();

#endif