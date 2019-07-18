#ifndef AUTOMATA_FILE_H
#define AUTOMATA_FILE_H

typedef struct TextFile TextFile;

struct TextFileVtbl {
	int(*load)(TextFile* self, const char* filepath);
	int(*unload)(TextFile* self);
};

struct TextFile {
	const struct TextFileVtbl* vptr;
	char* text;
	int length;
};

void TextFile_ctor(TextFile* self);

#endif
