#include <glad/glad.h>
#include "../include/automata/renderer/shader.h"
#include "../include/automata/renderer/core.h"

Shader shader = { 0 };

float triangle[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

static void init() {
	Shader_ctor(&shader);
	shader.vptr->load(&shader, "./shader.vert", "./shader.frag");
}

static void draw() {
	/* set background color */
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

const Renderer renderer = {
	init,
	draw
};
