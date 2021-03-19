#ifndef INPUT_H
#define INPUT_H

#include "terminal.h"

#define CTRL_KEY(k) ((k) & 0x1F)

void editorProcessKeypress(struct editorConfig* e);
void editorMoveCursor(int key, struct editorConfig* e);

#endif