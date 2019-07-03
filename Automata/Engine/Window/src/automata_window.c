#include "../src/internal_windows.h";
#include "../include/automata/window.h";

void automataWindowInit() {
	internal_initWindows();
}

void automataWindowCreate(int width, int height, const char* title) {
	internal_createWindows(width, height, title);
}

int automataWindowShouldClose() {
	return internal_shouldCloseWindows();
}