#include "../src/internal_windows.h"
#include "../include/automata/window.h"

const Window window = {
	internal_windowCreate,
	internal_windowClose,
	internal_windowShouldClose,
	internal_windowUpdate,
	internal_windowSwapBuffers,
	internal_windowGetWidth,
	internal_windowGetHeight,
	internal_windowSetSize,
	internal_windowSetTitle,
	internal_windowCenter
};
