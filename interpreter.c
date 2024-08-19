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
	char *command = strtok(args->command, "\n");
	char *bin = strtok(command, " ");
	char *_args = strtok(NULL, " ");
	char *_env = &args->env[0][0];

	if (!bin)
	{
		free(command);
		free(bin);
		free(_args);
		return (EXIT_SUCCESS);
	}
	free(command);


	status = execute(args->name, bin,_args , _env);
	return (status);
}
