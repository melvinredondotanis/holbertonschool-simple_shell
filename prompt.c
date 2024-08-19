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
	int read;

	printf("($) ");
	read = getline(&args->command, len, stdin);
	if (read == -1)
	{
		if (errno == 0)
		{
			putchar('\n');
			exit(EXIT_SUCCESS);
		}
		perror(args->name);
		free(args->name);
		free(args->command);
		free(args);
		exit(EXIT_FAILURE);
	}
}
