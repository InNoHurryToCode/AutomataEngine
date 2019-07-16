#include "../src/internal_windows.h"
#include "../include/automata/window.h"

int automataWindowCreate(int width, int height, const char* title) {
	return internal_windowCreate(width, height, title);
}

void automataWindowDestroy() {
	internal_windowDestroy();
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

int automataWindowGetWidth() {
	return internal_WindowGetWidth();
}

int automataWindowGetHeight() {
	return internal_WindowGetHeight();
}

void automataWindowSetSize(int width, int height) {
	internal_WindowSetSize(width, height);
}

void automataWindowSetTitle(const char* title) {
	internal_WindowSetTitle(title);
}

void automataWindowCenter() {
	internal_WindowCenter();
}
