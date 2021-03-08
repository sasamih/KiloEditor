#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "terminal.h"
#include "input.h"
#include "output.h"
#include "init.h"
#include "append_buffer.h"
 
struct editorConfig E;

int main()
{
    enableRawMode(&E);
    initEditor(&E);

    while (1)
    {
        editorRefreshScreen(&E);
        editorProcessKeypress(&E);
    }

    restoreOriginalTerminalConfig(&E);
    return 0;
}