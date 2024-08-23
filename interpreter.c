#include "simple_shell.h"

/**
 * _getenv - get the value of an environment variable
 * @name: name of the environment variable
 * This is the real getenv function source code, FUCK YOU BETTY!!!
 * 
 * Return: value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	char **ep;
	size_t len;

	if (__environ == NULL || name[0] == '\0')
		return (NULL);

	len = strlen(name);
	for (ep = __environ; *ep != NULL; ++ep)
		if (name[0] == (*ep)[0] && strncmp(name, *ep, len) == 0 && (*ep)[len] == '=')
			return (*ep + len + 1);

	return (NULL);
}

/**
 * interpreter - interpreter
 * @args: arguments
 *
 * Return: status
 */
int interpreter(arguments_t *args)
{
	int status, fd;
	char *_args[3], *tmp, *path_token;
	char *path = strdup(_getenv("PATH"));
	struct stat file_stat;

	args->nb_commands++;
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

	if (_args[0][0] == '.' && _args[0][1] == '\0')
	{
		print_error(args, "not enough arguments");
		free(path);
		free(args->command);
		return (EXIT_FAILURE);
	}

	if (_args[0][0] == '/' || _args[0][0] == '.')
	{
		fd = open(_args[0], O_RDONLY);
		if (fd == -1)
		{
			print_error(args, "");
			return (EXIT_FAILURE);
		}

		if (fstat(fd, &file_stat) == -1)
		{
			print_error(args, "");
			close(fd);
			return (EXIT_FAILURE);
		}

		status = execute(args, _args, args->env);
		free(path);
		free(args->command);
		close(fd);
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
			status = execute(args, _args, args->env);
			free(tmp);
			free(path);
			free(args->command);
			return (status);
		}
		free(tmp);
		path_token = strtok(NULL, ":");
	}

	print_error(args, "not found");
	free(path);
	free(args->command);
	return (EXIT_FAILURE);
}
