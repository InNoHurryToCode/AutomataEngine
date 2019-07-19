#ifndef AUTOMATA_RENDERER_H
#define AUTOMATA_RENDERER_H

typedef struct Renderer {
	void(*init)();
	void(*draw)();
} Renderer;

extern const Renderer renderer;

#endif
