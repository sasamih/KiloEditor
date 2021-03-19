#include "init.h"

void initEditor(struct editorConfig* e)
{
    e->cx = 0;
    e->cy = 0;

    if (getWindowSize(&e->screenrows, &e->screencols) == -1)
        die("getWindowSize");
}