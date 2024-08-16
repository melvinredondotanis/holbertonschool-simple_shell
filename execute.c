#include "simple_shell.h"

/**
 * execute - execute a program
 * @bin: program to execute
 * @args: arguments
 *
 * Return: 0
 */
int execute(char *bin, char *args)
{
	int status;
	char *error_buffer;
	pid_t pid = fork();

	error_buffer = malloc(1024);
	if (error_buffer == NULL)
	{
		perror("simple_shell: ");
		exit(EXIT_FAILURE);
	}
	if (pid == -1)
	{
		perror("simple_shell: ");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(bin, &args, NULL) == -1)
		{
			sprintf(error_buffer, "simple_shell: %s", bin);
			perror(error_buffer);
			free(error_buffer);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);

	free(error_buffer);
	return (0);
}
