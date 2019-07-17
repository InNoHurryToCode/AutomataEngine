#ifndef AUTOMATA_RENDERER_SHADER_H
#define AUTOMATA_RENDERER_SHADER_H

#include <glad/glad.h>

typedef struct shader shader;

struct shaderVtbl {
	int(*create)(shader* self, const char* vertexShader, const char* fragmentShader);
	void(*use)(shader* self);
	void(*setBool)(shader* self, const char* name, GLboolean value);
	void(*setInt)(shader* self, const char* name, GLint value);
	void(*setFloat)(shader* self, const char* name, GLfloat value);
};

struct shader {
	struct shaderVtbl* vptr;
	GLuint id;
};

void shader_ctor(shader* self);

#endif
