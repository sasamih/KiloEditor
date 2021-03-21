#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>

typedef struct erow
{
    int size;
    char* chars;
} erow;

struct editorConfig
{
    int cx, cy;
    int rowoff;
    int screenrows;
    int screencols;
    int numrows;
    erow* row;
    struct termios o_termios;
};

enum cursorKey
{
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    PAGE_UP,
    PAGE_DOWN,
    HOME_KEY,
    END_KEY,
    DEL_KEY
};

void die(const char *s);
void restoreOriginalTerminalConfig(struct editorConfig* e);
void enableRawMode(struct editorConfig* e);
int editorReadKey();
int getWindowSize(int* rows, int* cols);
void editorOpen(struct editorConfig* e, char* filename);

#endif