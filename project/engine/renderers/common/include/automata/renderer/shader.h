#ifndef AUTOMATA_RENDERER_SHADER_H
#define AUTOMATA_RENDERER_SHADER_H

#include <glad/glad.h>

typedef struct Shader Shader;

struct ShaderVtbl {
	int(*load)(Shader* self, const char* vertexShader, const char* fragmentShader);
	void(*use)(Shader* self);
	void(*setBool)(Shader* self, const char* name, GLboolean value);
	void(*setInt)(Shader* self, const char* name, GLint value);
	void(*setFloat)(Shader* self, const char* name, GLfloat value);
};

struct Shader {
	const struct ShaderVtbl* vptr;
	GLuint id;
};

void Shader_ctor(Shader* self);

#endif
