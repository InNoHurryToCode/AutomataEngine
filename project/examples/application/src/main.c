#include <stdio.h>
#include <stdlib.h>
#include <automata/window.h>
#include <automata/input.h>
#include <automata/renderer/core.h>

int main(int argc, char** argv) {
	printf("%s\n", argv[0]);
	
	/* create window */
	window.init(1280, 720, "Automata engine");
	renderer.init();

	/* application loop */
	while (!window.shouldClose()) {
		/* update automata */
		window.update();
		input.update();

		/* application update */
		if (input.getKey(AUTOMATA_KEY_ESC)) {
			window.close();
		}

		renderer.draw();

		/* update window buffers */
		window.swapBuffers();
	}

	return EXIT_SUCCESS;
}
