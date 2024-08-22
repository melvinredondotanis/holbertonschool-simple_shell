#include "simple_shell.h"

/**
 * _getenv - get the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	char *value, *env_name, *env_value;

	if (!name)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		env_name = strtok(environ[i], "=");
		env_value = strtok(NULL, "=");
		if (env_name && env_value && strcmp(env_name, name) == 0)
		{
			value = env_value;
			break;
		}
	}

	return (value);
}

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
	char *path = strdup(_getenv("PATH"));

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
