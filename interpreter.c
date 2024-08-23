#include "simple_shell.h"

/**
 * _getenv - get the value of an environment variable
 * @name: name of the environment variable
 * This is the real getenv function source code, FUCK YOU BETTY!!!
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
 * execute_command - execute the command
 * @args: arguments
 * @command: command to execute
 * Return: status
 */
int execute_command(arguments_t *args, char *command)
{
	int status, fd;
	char *_args[3], *tmp, *path, *path_token;
	struct stat file_stat;

	_args[0] = strtok(command, " "), _args[1] = strtok(NULL, " ");
	_args[2] = NULL;
	if (!_args[0])
	{
		free(args->command);
		return (EXIT_FAILURE);
	}
	if (_args[0][0] == '.' && _args[0][1] == '\0')
	{
		print_error(args, "not enough arguments"), free(args->command);
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
			print_error(args, ""), close(fd);
			return (EXIT_FAILURE);
		}
		status = execute(args, _args, args->env), free(args->command), close(fd);
		return (status);
	}
	path = strdup(_getenv("PATH")), path_token = strtok(path, ":");
	while (path_token)
	{
		tmp = malloc(strlen(path_token) + strlen(_args[0]) + 2);
		if (!tmp)
		{
			free(args->command);
			return (EXIT_FAILURE);
		}
		strcpy(tmp, path_token), strcat(tmp, "/"), strcat(tmp, _args[0]);
		if (access(tmp, X_OK) == 0)
		{
			_args[0] = tmp;
			status = execute(args, _args, args->env);
			free(tmp), free(args->command), free(path);
			return (status);
		}
		free(tmp), path_token = strtok(NULL, ":");
	}
	print_error(args, "not found"), free(args->command), free(path);
	return (EXIT_FAILURE);
}

/**
 * interpreter - interpreter
 * @args: arguments
 *
 * Return: status
 */
int interpreter(arguments_t *args)
{
	args->nb_commands++;
	if (!args || !args->command)
		return (EXIT_SUCCESS);

	return (execute_command(args, args->command));
}
