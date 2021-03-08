#include "terminal.h"

struct editorConfig
{
    struct termios o_termios;
};

struct editorConfig E;

void die(const char *s)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);
    exit(1);
}

void restoreOriginalTerminalConfig()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.o_termios) == -1)
        die("tcsetattr");
}

void enableRawMode()
{
    struct termios raw;

    if (tcgetattr(STDIN_FILENO, &E.o_termios) == -1)
        die("tcgetattr");
    atexit(restoreOriginalTerminalConfig);
    raw = E.o_termios;

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
