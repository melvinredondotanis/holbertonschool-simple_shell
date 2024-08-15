#include "simple_shell.h"

/**
 * execute - execute a command
 * @bin: binary
 * @args: arguments
 * Return: 0
 */
int execute(char *bin, char *args)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(bin, &args, NULL) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
	return (0);
}
