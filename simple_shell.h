#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int execute(char *bin, char *args);
int interpreter(char **command);
int prompt(char **line, size_t *len);

#endif /* SIMPLE_SHELL_H */
