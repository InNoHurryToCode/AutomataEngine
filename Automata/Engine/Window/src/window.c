#include "../src/internal_windows.h";
#include "../include/automata/window.h";

int automataWindowCreate(int width, int height, const char* title) {
	return internal_windowCreate(width, height, title);
}

int automataWindowDestroy() {
	return internal_windowDestroy();
}

int automataWindowShouldClose() {
	return internal_windowShouldClose();
}

void automataWindowUpdate() {
	internal_windowUpdate();
}

void automataWindowSwapBuffers() {
	internal_windowSwapBuffers();
}