#include "simple_shell.h"

/**
 * interpreter - interpreter
 * @args: arguments
 *
 * Return: status
 */
int interpreter(arguments_t *args)
{
	int status;
	char *_args[3], *tmp, *path_token;
	char *path = strdup(getenv("PATH"));

	if (!args || !args->command)
		return (EXIT_SUCCESS);

	_args[0] = strtok(args->command, " ");
	_args[1] = strtok(NULL, " ");
	_args[2] = NULL;
	if (!_args[0])
	{
		free(path);
		free(args->command);
		return (EXIT_FAILURE);
	}

	if (_args[0][0] == '/')
	{
		status = execute(args->name, _args, args->env);
		free(path);
		free(args->command);
		return (status);
	}

	path_token = strtok(path, ":");
	while (path_token)
	{
		tmp = malloc(strlen(path_token) + strlen(_args[0]) + 2);
		if (!tmp)
		{
			free(args->command);
			return (EXIT_FAILURE);
		}

		strcpy(tmp, path_token);
		strcat(tmp, "/");
		strcat(tmp, _args[0]);
		if (access(tmp, X_OK) == 0)
		{
			_args[0] = tmp;
			status = execute(args->name, _args, args->env);
			free(tmp);
			free(path);
			free(args->command);
			return (status);
		}
		free(tmp);
		path_token = strtok(NULL, ":");
	}

	perror(args->name);
	free(path);
	free(args->command);
	return (EXIT_FAILURE);
}
