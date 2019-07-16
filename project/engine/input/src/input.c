#include "../src/internal_windows.h"
#include "../include/automata/input.h"

void automataInputUpdate() {
	internal_inputUpdate();
}

int automataInputGetAxis(AutomataAxis axis) {
	return internal_inputGetAxis(axis);
}

int automataInputGetKey(AutomataKeys key) {
	return internal_inputGetKey(key);
}

AutomataKeys automataInputDetectKey() {
	return internal_inputDetectKey();
}
