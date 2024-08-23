#include "simple_shell.h"

/**
 * execute - execute the command
 * @args: name of the program
 * @command: command
 * @env: environment
 *
 * Return: 0 on success, 1 on failure
 */
int execute(arguments_t *args, char **command, char **env)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		print_error(args, "");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(command[0], command, env) == -1)
		{
			print_error(args, "");
			return (EXIT_FAILURE);
		}
	}
	else
		wait(&status);

	return (WEXITSTATUS(status));
}
