#include "simple_shell.h"

/**
 * cleanup - clean up the arguments
 * @args: arguments
 */
void cleanup(arguments_t *args)
{
	if (args)
	{
		if (args->name)
			free(args->name);
		if (args->command)
			free(args->command);
		free(args);
	}
}
