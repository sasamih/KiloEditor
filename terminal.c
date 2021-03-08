#include "terminal.h"

void die(const char *s)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);
    exit(1);
}

void restoreOriginalTerminalConfig(struct editorConfig* e)
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &e->o_termios) == -1)
        die("tcsetattr");
}

void enableRawMode(struct editorConfig* e)
{
    struct termios raw;

    if (tcgetattr(STDIN_FILENO, &e->o_termios) == -1)
        die("tcgetattr");
    //atexit(restoreOriginalTerminalConfig);
    raw = e->o_termios;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");;
}

char editorReadKey()
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }

    return c;
}

int getWindowSize(int* rows, int* cols)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
    {
        return -1;
    }
    else
    {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }  
}

int getCursorPosition(int* rows, int* cols)
{
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return -1;

    printf("\r\n");
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        if (iscntrl(c))
        {
            printf("%d\r\n", c);
        }
        else
        {
            printf("%d ('%c')\r\n", c, c);
        }
    }
    editorReadKey();
    return -1;
}
