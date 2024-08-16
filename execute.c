#include "simple_shell.h"

/**
 * execute - execute a program
 * @bin: program to execute
 * @args: arguments
 * @program_name: name of the program
 *
 * Return: 0
 */
int execute(char *bin, char *args, char *program_name)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror(program_name);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(bin, &args, NULL) == -1)
		{
			perror(program_name);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);

	return (0);
}
