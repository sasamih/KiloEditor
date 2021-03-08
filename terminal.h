#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

void die(const char *s);
void restoreOriginalTerminalConfig();
void enableRawMode();
char editorReadKey();

#endif