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
	char *_args[3];

	_args[0] = strtok(args->command, " ");
	_args[1] = strtok(NULL, " ");
	_args[2] = NULL;
	if (!_args[0])
	{
		free(_args[0]);
		free(_args[1]);
		free(_args[2]);	
		return (EXIT_SUCCESS);
	}

	status = execute(args->name, _args, args->env);
	free(_args[0]);
	free(_args[1]);
	free(_args[2]);
	return (status);
}
