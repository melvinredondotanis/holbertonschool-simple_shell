#include "simple_shell.h"

/**
 * prompt - prints prompt and reads input
 * @line: pointer to buffer
 * @len: pointer to buffer size
 * @program_name: name of the program
 *
 * Return: number of characters read
 */
int prompt(char **line, size_t *len, char *program_name)
{
	int read;

	printf("($) ");
	read = getline(line, len, stdin);
	if (read == -1)
	{
		if (errno == 0)
		{
			putchar('\n');
			exit(EXIT_SUCCESS);
		}
		perror(program_name);
		exit(EXIT_FAILURE);
	}
	return (read);
}
