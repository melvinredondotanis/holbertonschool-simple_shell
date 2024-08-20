#include "simple_shell.h"

/**
 * prompt - prompt the user for a command
 * @args: arguments
 * @len: length of the command
 * @mode: mode
 *
 * Return: number of characters read
 */
void prompt(arguments_t *args, size_t *len, int mode)
{
	if (mode)
		printf("($) ");

	errno = 0;
	if (getline(&args->command, len, stdin) == -1)
	{
		if (errno == 0)
			exit(EXIT_SUCCESS);
		else
		{
			perror(args->name);
			cleanup(args);
			exit(EXIT_FAILURE);
		}
	}
}
