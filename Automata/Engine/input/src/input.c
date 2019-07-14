#include "../src/internal_windows.h";
#include "../include/automata/input.h";

void automataInputUpdate() {
	internal_inputUpdate();
}

int automataInputGetKey(int key) {
	return internal_inputGetKey(key);
}

int automataInputDetectKey() {
	return internal_inputDetectKey();
}