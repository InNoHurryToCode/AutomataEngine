#include <stdlib.h>
#include <automata/window.h>
#include <automata/input.h>

int main(int argc, char** argv) {
	/* initialize automata */
	automataWindowCreate(1280, 720, "Automata engine");

	/* application loop */
	while (!automataWindowShouldClose()) {
		/* update automata */
		automataWindowUpdate();
		automataInputUpdate();

		/* application update */
		if (automataInputGetKey(AUTOMATA_KEY_ESC)) {
			automataWindowDestroy();
		}

		/* update window buffers */
		automataWindowSwapBuffers();
	}

	/* destroy automata */
	automataWindowDestroy();
	return EXIT_SUCCESS;
}
