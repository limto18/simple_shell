#include "main.h"

/**
 * env - print the environ
 * @path: list of directory in path
 * @args: list of arguments
 */
void env(list_t *path __attribute__((unused)),
char **args __attribute__((unused)))
{
	char **env;

	env = environ;
	while (*env)
	{
		print(*env, STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
		env++;
	}
}

/**
 * handle_exit - exit the shell
 * @path: list of directory in path
 * @args: list of arguments
 */
void handle_exit(list_t *path, char **args)
{
	free_list(path);
	free(args);

	exit(2);
}
