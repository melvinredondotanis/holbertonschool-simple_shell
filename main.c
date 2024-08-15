#include "simple_shell.h"

/**
 * main - entry point
 *
 * Return: 0
 */
int main(void)
{
	int status = 0;
	char *line = NULL, **ptr_line = &line;
	size_t len = 0;

	if (!isatty(STDIN_FILENO))
	{
		while (getline(ptr_line, &len, stdin) != -1)
		{
			status = interpreter(ptr_line);
			if (status == -1)
			{
				free(*ptr_line);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		while (1)
		{
			if (prompt(ptr_line, &len) == -1)
			{
				free(*ptr_line);
				exit(EXIT_FAILURE);
			}

			status = interpreter(ptr_line);
			if (status == -1)
			{
				free(*ptr_line);
				exit(EXIT_FAILURE);
			}
		}
	}
	free(*ptr_line);
	return (status);
}
