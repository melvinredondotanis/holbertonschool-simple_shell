#include "simple_shell.h"

int interpreter(char **command)
{
	int status = 0;
	char *token;
	char *clear_token;

	clear_token = strtok(*command, "\n");
	token = strtok(clear_token, " ");
	while (token != NULL)
	{
		if (token[0] == '.' && token[1] == '/')
		{
			printf("exec local binary: %s\n", token);
			token = strtok(NULL, " ");
			if (token != NULL)
				printf("with: %s\n", token);
			status = 1;
		}
		else if (token[0] == '/')
		{
			char *params = strtok(NULL, " ");
			if (execute(token, params) == 0)
				status = 0;
			else
				printf("Command not found: %s\n", token);
		}
		else if ((token[0] >= 'A' && token[0] <= 'Z') || (token[0] >= 'a' && token[0] <= 'z'))
		{
			printf("exec command: %s\n", token);
			token = strtok(NULL, " ");
			if (token != NULL)
				printf("with: %s\n", token);
			status = 1;
		}
		token = strtok(NULL, " ");
	}
	return (status);
}
