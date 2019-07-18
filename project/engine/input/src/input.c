#include "../src/internal_windows.h"
#include "../include/automata/input.h"

const Input input = {
	internal_inputUpdate,
	internal_inputGetAxis,
	internal_inputGetKey,
	internal_inputDetectKey
};