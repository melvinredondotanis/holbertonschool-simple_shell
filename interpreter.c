#include "simple_shell.h"

/**
 * interpreter - interprets a command
 * @command: pointer to command
 * @program_name: name of the program
 * @env: environment
 *
 * Return: 0
 */
int interpreter(char **command, char *program_name, char *env)
{
	int status = 0;
	char *token;

	token = strtok(*command, "\n");
	for (; token != NULL; token = strtok(NULL, " "))
	{
		if (execute(token, strtok(NULL, " "), program_name, env) == 0)
			status = 0;
	}
	return (status);
}
