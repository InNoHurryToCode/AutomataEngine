#include <stdio.h>
#include <stdlib.h>
#include "../include/automata/file.h"

static int internal_getFileSize(FILE* file) {
	int size = 0;

	if (!file) {
		return 0;
	}
	
	/* get size */
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	return size;
}

static int internal_load(TextFile* self, const char* filepath) {
	FILE* file = NULL;
	char* text = NULL;
	int size = 0;

	if (!self) {
		return 0;
	}

	/* open file */
	file = fopen(filepath, "rb");

	if (!file) {
		printf("ERROR: file %s doesn't exist\n", filepath);
		return 0;
	}

	/* get file size */
	size = internal_getFileSize(file);

	if (size == 0) {
		printf("ERROR: failed to get file size of %s\n", filepath);
		return 0;
	}

	/* allocate memory for the text */
	text = malloc(size);

	if (!text) {
		printf("ERROR: failed to allocate memory for %s\n", filepath);
		return 0;
	}

	/* read file */
	fread(text, 1, size, file);
	fclose(file);

	/* assign values */
	self->text = text;
	self->length = size;
	return 1;
}

static int internal_unload(TextFile* self) {
	if (!self) {
		return 0;
	}

	free(self->text);
	return 1;
}

static const struct TextFileVtbl textFileVtbl = {
	internal_load,
	internal_unload
};

void TextFile_ctor(TextFile* self) {
	if (!self) {
		return;
	}

	self->vptr = &textFileVtbl;
	self->text = NULL;
	self->length = 0;
}