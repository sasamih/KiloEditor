#include "init.h"

void initEditor(struct editorConfig* e)
{
    if (getWindowSize(&e->screenrows, &e->screencols) == -1)
        die("getWindowSize");
}