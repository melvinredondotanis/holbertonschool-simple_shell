#include "simple_shell.h"

/**
 * interpreter - interprets a command
 * @command: pointer to command
 *
 * Return: 0
 */
int interpreter(char **command)
{
	int status = 0;
	char *token;

	token = strtok(*command, "\n");
	for (; token != NULL; token = strtok(NULL, " "))
	{
		if (execute(token, strtok(NULL, " ")) == 0)
			status = 0;
	}
	return (status);
}
