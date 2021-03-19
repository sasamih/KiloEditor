#include "input.h"
#include "terminal.h"

void editorProcessKeypress(struct editorConfig* e)
{
    int c = editorReadKey();

    switch(c)
    {
        case CTRL_KEY('q'):
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            restoreOriginalTerminalConfig(e);
            exit(0);
            break;

        case HOME_KEY:
            e->cx = 0;
            break;
            
        case END_KEY:
            e->cx = e->screencols - 1;
            break;

        case PAGE_UP:
        case PAGE_DOWN:
        {
            int times = e->screenrows;
            while (times--)
            editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN, e);
        }
        break;    

        case ARROW_LEFT:
        case ARROW_RIGHT:
        case ARROW_UP:
        case ARROW_DOWN:
            editorMoveCursor(c, e);
            break;

        default:
            break;
    }
}

void editorMoveCursor(int key, struct editorConfig* e)
{
    switch (key)
    {
    case ARROW_LEFT:
        if (e->cx != 0)
            e->cx--;
        break;
    case ARROW_DOWN:
        if (e->cy < e->screenrows - 1)
            e->cy++;
        break;
    case ARROW_RIGHT:
        if (e->cx < e->screencols - 1)
            e->cx++;
        break;
    case ARROW_UP:
        if (e->cy != 0)
            e->cy--;
        break;
    
    default:
        break;
    }
}