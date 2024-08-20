#include "simple_shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument value
 * @env: environment
 *
 * Return: 0
 */
int main(int argc, char **argv, char **env)
{
	int status;
	size_t len;
	arguments_t *args;
	(void)argc;

	args = malloc(sizeof(arguments_t));
	if (!args)
	{
		perror(argv[0]);
		cleanup(args);
		return (EXIT_FAILURE);
	}

	args->name = strdup(argv[0]);
	args->command = NULL;
	args->env = env;
	if (!args->name)
	{
		perror(argv[0]);
		cleanup(args);
		return (EXIT_FAILURE);
	}

	while (1)
	{
		prompt(args, &len, isatty(STDIN_FILENO));
		args->command = strtok(args->command, "\n");
		status = interpreter(args);
		args->command = NULL;
	}

	cleanup(args);
	return (status);
}
