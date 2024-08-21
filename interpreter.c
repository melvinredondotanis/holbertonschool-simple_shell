#include "simple_shell.h"

/**
 * interpreter - interprets the command
 * @args: arguments
 *
 * Return: exit status of the executed program
 */
int interpreter(arguments_t *args)
{
	int status;
	char *_args[3], *path = "/usr/bin/", *tmp;

	if (!args || !args->command)
		return (EXIT_SUCCESS);

	_args[0] = strtok(args->command, " ");
	_args[1] = strtok(NULL, " ");
	_args[2] = NULL;
	if (!_args[0])
	{
		free(args->command);
		return (EXIT_FAILURE);
	}

	if (_args[0][0] == '/')
	{
		status = execute(args->name, _args, args->env);
		free(args->command);
		return (status);
	}

	tmp = malloc(sizeof(char) * (strlen(path) + strlen(_args[0]) + 1));
	if (tmp == NULL)
	{
		perror(args->name);
		free(args->command);
		return (EXIT_FAILURE);
	}

	strcpy(tmp, path);
	strcat(tmp, _args[0]);
	_args[0] = tmp;
	if (access(_args[0], X_OK) == -1)
	{
		perror(args->name);
		free(tmp);
		free(args->command);
		return (EXIT_FAILURE);
	}

	status = execute(args->name, _args, args->env);
	free(tmp);
	free(args->command);
	return (status);
}
