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
	int status = 0;
	size_t len = 0;
	arguments_t *args = malloc(sizeof(arguments_t));
	(void)argc;
	if (!args)
	{
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	args->name = strtok(argv[0], "\n");
	args->command = malloc(sizeof(char *)), args->env = env;
	if (!isatty(STDIN_FILENO))
		if (getline(&(args->command), &len, stdin) != -1)
		{
			status = interpreter(args);
			if (status == -1)
			{
				free(args->command);
				free(args);
				exit(EXIT_FAILURE);
			}
			return (status);
		}
	while (1)
	{
		if (prompt(args, &len) == -1)
		{
			free(args->command);
			free(args);
			exit(EXIT_FAILURE);
		}
		status = interpreter(args);
		if (status == -1)
		{
			free(args->command);
			free(args);
			exit(EXIT_FAILURE);
		}
	}
	return (status);
}
