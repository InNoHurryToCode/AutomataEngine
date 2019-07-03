#include <stdlib.h>
#include <automata/window.h>

int main(int argc, char** argv) {
	automataWindowCreate(1280, 720, "Automata engine");

	while (!automataWindowShouldClose()) {
		automataWindowUpdate();
		automataWindowSwapBuffers();
	}

	automataWindowDestroy();
	return EXIT_SUCCESS;
}