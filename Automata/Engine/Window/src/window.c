#include "../src/internal_windows.h";
#include "../include/automata/window.h";

void automataWindowCreate(int width, int height, const char* title) {
	internal_create(width, height, title);
}

void automataWindowDestroy() {
	internal_destroy();
}

int automataWindowShouldClose() {
	return internal_shouldClose();
}

void automataWindowUpdate() {
	internal_update();
}