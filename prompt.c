#include "simple_shell.h"

/**
 * prompt - prints prompt and reads input
 * @line: pointer to buffer
 * @len: pointer to buffer size
 *
 * Return: number of characters read
 */
int prompt(char **line, size_t *len)
{
	int read;

	printf("$ ");
	read = getline(line, len, stdin);
	if (read == -1)
	{
		perror("getline failed");
		exit(EXIT_FAILURE);
	}
	return (read);
}
