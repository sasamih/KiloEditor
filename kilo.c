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
 
// #define _DEFAULT_SOURCE
// #define _BSD_SOURCE
// #define _GNU_SOURCE

struct editorConfig E;

int main(int argc, char* argv[])
{
    enableRawMode(&E);
    initEditor(&E);
    if (argc >= 2)
    {
        editorOpen(&E, argv[1]);
    }

    while (1)
    {
        editorRefreshScreen(&E);
        editorProcessKeypress(&E);
    }

    restoreOriginalTerminalConfig(&E);
    return 0;
}