#include <unistd.h>

#include "output.h"

void editorRefreshScreen(struct editorConfig* e)
{
    struct abuf ab = ABUF_INIT;
    abAppend(&ab, "\x1b[?25l", 6);
    abAppend(&ab, "\x1b[2J", 4);
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(e, &ab);
    abAppend(&ab, "\x1b[H", 3);
    abAppend(&ab, "\x1b[?25h", 6);
    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

void editorDrawRows(struct editorConfig* e, struct abuf* ab)
{
    int y;
    for (y = 0; y < e->screenrows; y++)
    {
        abAppend(ab, "~", 1);
        // write(STDOUT_FILENO, "~", 1);
        if (y < e->screenrows - 1)
        {
            abAppend(ab, "\r\n", 2);
            // write(STDOUT_FILENO, "\r\n", 2);
        }
    }
}