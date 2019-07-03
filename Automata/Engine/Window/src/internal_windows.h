#ifndef INTERNAL_WINDOWS_H
#define INTERNAL_WINDOWS_H

void internal_create(int width, int height, const char* title);
void internal_destroy();
int internal_shouldClose();
void internal_update();

#endif