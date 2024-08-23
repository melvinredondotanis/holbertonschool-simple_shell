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
		printf("%s: %d: %s:", args->name, args->nb_commands, args->command);
		fflush(stdout);
		perror("");
	}
	else
		printf("%s: %d: %s: %s\n", args->name, args->nb_commands, args->command, msg);
}
