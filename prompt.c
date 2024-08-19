#include "simple_shell.h"

/**
 * prompt - prompt the user for a command
 * @args: arguments
 * @len: length of the command
 *
 * Return: number of characters read
 */
void prompt(arguments_t *args, size_t *len)
{
	printf("($) ");
	if (getline(&args->command, len, stdin) == -1)
	{
		if (errno == 0)
			putchar('\n');

		perror(args->name);
		cleanup(args);
		exit(EXIT_FAILURE);
	}
}
