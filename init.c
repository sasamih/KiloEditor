#include "init.h"

void initEditor(struct editorConfig* e)
{
    e->cx = 0;
    e->cy = 0;
    e->rowoff = 0;
    e->numrows = 0;
    e->row = NULL;

    if (getWindowSize(&e->screenrows, &e->screencols) == -1)
        die("getWindowSize");
}