#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

extern char **environ;

/**
 * struct arguments - structure for arguments
 * @name: name of the programEXIT_SUCCESS
 * @command: command
 * @env: environment
 * @nb_commands: number of commands
 */
typedef struct arguments
{
	char *name;
	char *command;
	char **env;
	int nb_commands;
} arguments_t;

void print_error(arguments_t *args, char *msg);
void cleanup(arguments_t *args);
int execute(arguments_t *args, char **command, char **env);
int interpreter(arguments_t *args);
void prompt(arguments_t *args, size_t *len, int mode);

#endif /* SIMPLE_SHELL_H */
