#include <unistd.h>
#include <stdio.h>

#include "output.h"

#define KILO_VERSION "0.0.1"

void editorRefreshScreen(struct editorConfig* e)
{
    struct abuf ab = ABUF_INIT;
    // abAppend(&ab, "\x1b[?25l", 6);
    write(STDOUT_FILENO, "\x1b[?25l", 6);
    // abAppend(&ab, "\x1b[2J", 4);
    // abAppend(&ab, "\x1b[H", 3);
    write(STDOUT_FILENO, "\x1b[H", 3);

    editorDrawRows(e, &ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", e->cy + 1, e->cx + 1);
    write(STDOUT_FILENO, buf, strlen(buf));

    // abAppend(&ab, "\x1b[H", 3);
    // write(STDOUT_FILENO, "\x1b[H", 3);
    // abAppend(&ab, "\x1b[?25h", 6);
    write(STDOUT_FILENO, "\x1b[?25h", 6);
    // write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

void editorDrawRows(struct editorConfig* e, struct abuf* ab)
{
    int y;
    for (y = 0; y < e->screenrows; y++)
    {
        if (y == e->screenrows / 3)
        {
            char welcome[80];
            int welcomelen = snprintf(welcome, sizeof(welcome),
                "Kilo editor -- version %s", KILO_VERSION);
            if (welcomelen > e->screencols) welcomelen = e->screencols;
            int padding = (e->screencols - welcomelen) / 2;
            if (padding)
            {
                write(STDOUT_FILENO, "~", 1);
                padding--;
            }
            while (padding--)
            {
                write(STDOUT_FILENO, " ", 1);
            }

            // abAppend(ab, welcome, welcomelen);
            write(STDOUT_FILENO, welcome, welcomelen);
        }
        else
        {
            write(STDOUT_FILENO, "~", 1);
            // abAppend(ab, "~", 1);
        }
        // abAppend(ab, "\x1b[K", 3);
        write(STDOUT_FILENO, "\x1b[K", 3);
        if (y < e->screenrows - 1)
        {
            // abAppend(ab, "\r\n", 2);
            write(STDOUT_FILENO, "\r\n", 2);
        }
    }
}