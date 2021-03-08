#include "input.h"
#include "terminal.h"

void editorProcessKeypress(struct editorConfig* e)
{
    char c = editorReadKey();

    switch(c)
    {
        case CTRL_KEY('q'):
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            restoreOriginalTerminalConfig(e);
            exit(0);
            break;

        default:
            break;
    }
}