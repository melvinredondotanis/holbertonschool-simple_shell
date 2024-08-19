#include "simple_shell.h"

/**
 * execute - execute the command
 * @name: name of the program
 * @command: command
 * @env: environment
 *
 * Return: 0
 */
int execute(char *name, char **command, char **env)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror(name);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(command[0], command, env) == -1)
		{
			perror(name);
			return (EXIT_FAILURE);
		}
	}
	else
		wait(&status);

	return (WEXITSTATUS(status));
}
