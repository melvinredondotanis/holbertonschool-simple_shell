#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

/**
 * struct arguments - structure for arguments
 * @name: name of the program
 * @command: command
 * @env: environment
 */
typedef struct arguments
{
	char *name;
	char *command;
	char **env;
} arguments_t;

int execute(char *name, char *bin, char *args, char *env);
int interpreter(arguments_t *args);
void prompt(arguments_t *args, size_t *len);

#endif /* SIMPLE_SHELL_H */
