#include "simple_shell.h"

/**
 * execute - execute the command
 * @name: name of the program
 * @bin: binary
 * @args: arguments
 * @env: environment
 *
 * Return: 0
 */
int execute(char *name, char *bin, char *args, char *env)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror(name);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(bin, &args, &env) == -1)
		{
			perror(name);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);

	return (WEXITSTATUS(status));
}
