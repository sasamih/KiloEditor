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

int editorReadKey()
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }

    if (c == '\x1b')
    {
        char seq[3];

        if (read(STDOUT_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDOUT_FILENO, &seq[1], 1) != 1) return '\x1b';

        if (seq[0] == '[')
        {
            if (seq[1] >= '0' && seq[1] <= '9') 
            {
                if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
                if (seq[2] == '~') 
                {
                    switch (seq[1]) 
                    {
                        case '1': return HOME_KEY;
                        case '3': return DEL_KEY;
                        case '4': return END_KEY;
                        case '5': return PAGE_UP;
                        case '6': return PAGE_DOWN;
                        case '7': return HOME_KEY;
                        case '8': return END_KEY;
                    }
                }
            } 
            else 
            {
                switch(seq[1])
                {
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                    case 'H': return HOME_KEY;
                    case 'F': return END_KEY;
                }
            }
        }
        else if (seq[0] == 'O')
        {
            switch (seq[1])
            {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;    
            }
        }
        
        return '\x1b';
    }
    else
    {
        return c;
    }
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

static void editorAppendRow(struct editorConfig* e, char* s, size_t len)
{
    e->row = realloc(e->row, sizeof(erow) * (e->numrows + 1));

    int at = e->numrows;
    e->row[at].size = len;
    e->row[at].chars = malloc(len + 1);
    memcpy(e->row[at].chars, s, len);
    e->row[at].chars[len] = '\0';
    e->numrows++;
}

void editorOpen(struct editorConfig* e, char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (!fp) die("fopen");

    char* line = NULL;
    ssize_t linelen;
    size_t linecap = 0;

    while ((linelen = getline(&line, &linecap, fp)) != -1)
    {
        while(linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
        {
            linelen--;
        }
        editorAppendRow(e, line, linelen);
    }
    free(line);
    fclose(fp);
}
