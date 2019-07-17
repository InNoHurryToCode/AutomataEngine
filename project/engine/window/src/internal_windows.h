#ifndef INTERNAL_WINDOWS_H
#define INTERNAL_WINDOWS_H

int internal_windowCreate(int width, int height, const char* title);
void internal_windowDestroy();
int internal_windowShouldClose();
void internal_windowUpdate();
void internal_windowSwapBuffers();
int internal_windowGetWidth();
int internal_windowGetHeight();
void internal_windowSetSize(int width, int height);
void internal_windowSetTitle(const char* title);
void internal_windowCenter();

#endif
