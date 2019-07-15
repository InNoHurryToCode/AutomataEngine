#ifndef INTERNAL_WINDOWS_H
#define INTERNAL_WINDOWS_H

int internal_windowCreate(int width, int height, const char* title);
void internal_windowDestroy();
int internal_windowShouldClose();
void internal_windowUpdate();
void internal_windowSwapBuffers();
int internal_WindowGetWidth();
int internal_WindowGetHeight();
void internal_WindowSetSize(int width, int height);
void internal_WindowSetTitle(const char* title);
void internal_WindowCenter();

#endif
