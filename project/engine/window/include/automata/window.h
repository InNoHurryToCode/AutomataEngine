#ifndef AUTOMATA_WINDOW_H
#define AUTOMATA_WINDOW_H

typedef struct Window {
	int(*init)(int width, int height, const char* title);
	void(*close)();
	int(*shouldClose)();
	void(*update)();
	void(*swapBuffers)();
	void(*getWidth)();
	void(*getHeight)();
	void(*setSize)(int width, int height);
	void(*setTitle)(const char* title);
	void(*center)();
} Window;

extern const Window window;

#endif
