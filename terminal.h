#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

struct editorConfig
{
    int screenrows;
    int screencols;
    struct termios o_termios;
};

void die(const char *s);
void restoreOriginalTerminalConfig(struct editorConfig* e);
void enableRawMode(struct editorConfig* e);
char editorReadKey();
int getWindowSize(int* rows, int* cols);

#endif