#include "simple_shell.h"

/**
 * print_error - print error
 * @args: arguments
 * @msg: message
 */
void print_error(arguments_t *args, char *msg)
{
	if (msg[0] == '\0')
	{
		fprintf(stderr, "%s: %d: %s:", args->name, args->nb_commands, args->command);
		fflush(stderr);
		perror("");
	}
	else
		fprintf(stderr, "%s: %d: %s: %s\n", args->name, args->nb_commands, args->command, msg);
}
