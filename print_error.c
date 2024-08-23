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
		printf("%s: %d: ", args->name, args->nb_commands);
		fflush(stdout);
		perror("");
	}
	else
		printf("%s: %d: %s \n", args->name, args->nb_commands, msg);
}
