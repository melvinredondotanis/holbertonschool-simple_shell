#include "simple_shell.h"

/**
 * cleanup - clean up the arguments
 * @args: arguments
 */
void cleanup(arguments_t *args)
{
	if (args != NULL)
	{
		free(args->name);
		free(args->command);
		free(args);
	}
}

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
	int status = 0;
	size_t len = 0;
	arguments_t *args = malloc(sizeof(arguments_t));
	(void)argc;

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

	if (!isatty(STDIN_FILENO))
		if (getline(&args->command, &len, stdin) != -1)
		{
			status = interpreter(args);
			cleanup(args);
			return (status);
		}

	while (1)
	{
		prompt(args, &len);
		args->command = strtok(args->command, "\n");
		status = interpreter(args);
		args->command = NULL;
	}

	cleanup(args);
	return (status);
}
