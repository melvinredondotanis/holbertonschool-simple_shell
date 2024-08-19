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
	char *_command;
	size_t len;
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
	{
		while ((getline(&_command, &len, stdin)) != -1)
		{
			args->command = strtok(_command, "\n");
			while (args->command)
			{
				status = interpreter(args);
				args->command = strtok(NULL, " ");
			}
			args->command = NULL;
		}
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
