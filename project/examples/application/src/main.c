#include <stdlib.h>
#include <automata/window.h>
#include <automata/input.h>

int main(int argc, char** argv) {
	/* create window */
	if (!window.init(1280, 720, "Automata engine")) {
		return;
	}

	/* application loop */
	while (!window.shouldClose()) {
		/* update automata */
		window.update();
		input.update();

		/* application update */
		if (input.getKey(AUTOMATA_KEY_ESC)) {
			window.close();
		}

		/* update window buffers */
		window.swapBuffers();
	}

	return EXIT_SUCCESS;
}
