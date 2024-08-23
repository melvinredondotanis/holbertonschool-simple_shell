#include "simple_shell.h"

/**
 * print_error - print error
 * @args: arguments
 * @msg: message
 */
void print_error(arguments_t *args, char *msg)
{
	char *name = args->name, *command = args->command;
	char *nb_commands = args->nb_commands;

	if (msg[0] == '\0')
	{
		fprintf(stderr, "%s: %d: %s:", name, nb_commands, command);
		fflush(stderr);
		perror("");
	}
	else
		fprintf(stderr, "%s: %d: %s: %s\n", name, nb_commands, command, msg);
}
