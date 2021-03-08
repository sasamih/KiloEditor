#include <unistd.h>

#include "output.h"

void editorRefreshScreen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    editorDrawRows();
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void editorDrawRows()
{
    int y;
    for (y = 0; y < 24; y++)
    {
        write(STDOUT_FILENO, "~", 1);
        if (y < 23)
        {
            write(STDOUT_FILENO, "\r\n", 2);
        }
    }
}