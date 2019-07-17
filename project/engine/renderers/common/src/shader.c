#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/automata/renderer/shader.h"

#define LOG_SIZE 1024

static int internal_shaderGetCompileErrors(unsigned int shader, const char* type) {
	int success = 0;
	char log[LOG_SIZE] = { 0 };

	if (strcmp(type, "PROGRAM") == 0) {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		
		if (!success) {
			glGetProgramInfoLog(shader, LOG_SIZE, NULL, log);
			printf("ERROR: failed to link program of type: %s\n%s", type, log);
			return 0;
		}
	} else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		
		if (!success) {
			glGetShadersInfoLog(shader, LOG_SIZE, NULL, log);
			printf("ERROR: failed to compile shader of type: %s\n%s", type, log);
			return 0;
		}
	}

	return 1;
}

static int internal_shaderCreate(shader *self, const char* vertexShader, const char* fragmentShader) {
	FILE* vertexFile = NULL;
	FILE* fragmentFile = NULL;
	const char* vertexCode = "";
	const char* fragmentCode = "";
	GLuint vertex = 0;
	GLuint fragment = 0;
	
	if (!self) {
		return;
	}

	/* open file here */

	/* compile vertex shader */
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, vertexCode, NULL);
	glCompileShader(vertex);

	if (!internal_shaderGetCompileErrors(vertex, "VERTEX")) {
		return 0;
	}

	/* compile fragment shader */
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	
	if (!internal_shaderGetCompileErrors(fragment, "FRAGMENT")) {
		return 0;
	}

	/* create shader program */
	self->id = glCreateProgram();
	glAttachShader(self->id, vertex);
	glAttachShader(self->id, fragment);
	glLinkProgram(self->id);
	if (!internal_shaderGetCompileErrors(self->id, "PROGRAM")) {
		return 0;
	}

	/* cleanup */
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return 1;
}

static void internal_shaderUse(shader* self) {
	if (!self) {
		return;
	}

	glUseProgram(self->id);
}

static void internal_shaderSetBool(shader* self, const char* name, GLboolean value) {
	if (!self) {
		return;
	}

	glUniform1i(glGetUniformLocation(self->id, name), value);
}

static void internal_shaderSetInt(shader* self, const char* name, GLint value) {
	if (!self) {
		return;
	}

	glUniform1i(glGetUniformLocation(self->id, name), value);
}

static void internal_shaderSetFloat(shader* self, const char* name, GLfloat value) {
	if (!self) {
		return;
	}

	glUniform1i(glGetUniformLocation(self->id, name), value);
}

static struct shaderVtbl shaderVtbl = {
	internal_shaderCreate,
	internal_shaderUse,
	internal_shaderSetBool,
	internal_shaderSetInt,
	internal_shaderSetFloat
};

void shader_ctor(shader* self) {
	if (!self) {
		return;
	}

	self->vptr = &shaderVtbl;
	self->id = 0;
}
