#ifndef INTERNAL_WINDOWS_H
#define INTERNAL_WINDOWS_H

int internal_windowCreate(int width, int height, const char* title);
int internal_windowDestroy();
int internal_windowShouldClose();
void internal_windowUpdate();
void internal_windowSwapBuffers();

#endif