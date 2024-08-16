#include "simple_shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument value
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	int status = 0;
	char *program_name;
	char *line = NULL, **ptr_line = &line;
	size_t len = 0;
	(void)argc;

	program_name = strtok(argv[0], "\n");

	if (!isatty(STDIN_FILENO))
	{
		while (getline(ptr_line, &len, stdin) != -1)
		{
			status = interpreter(ptr_line, program_name);
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
			if (prompt(ptr_line, &len, program_name) == -1)
			{
				free(*ptr_line);
				exit(EXIT_FAILURE);
			}

			status = interpreter(ptr_line, program_name);
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
