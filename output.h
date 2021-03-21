#ifndef OUTPUT_H
#define OUTPUT_H

#include "terminal.h"
#include "append_buffer.h"

void editorRefreshScreen(struct editorConfig* e);
void editorDrawRows(struct editorConfig* e, struct abuf* ab);
void editorScroll(struct editorConfig* e);

#endif