#include "main.h"

/**
 * get_command_type - determine the type of the command
 * @path: list of command director
 * @command: the command to check
 *
 * Return: constant representing the type of the command
 * Description -
 *              EXTERNAL_COMMAND (1) command like "/bin/ls"
 *              INTERNAL_COMMAND (2) command like exit, env
 *              PATH_COMMAND (3) command found in path
 *              INVALID_COMMAND (-1) invalid command
 */
int get_command_type(list_t *path, char *command)
{
	int i;
	char *internal_commands[] = {"env", "exit", NULL}, *dir;

	if (_strchr(command, '/'))
		return (EXTERNAL_COMMAND);

	for (i = 0; internal_commands[i]; i++)
	{
		if (_strcmp(command, internal_commands[i]) == 0)
			return (INTERNAL_COMMAND);
	}

	dir = _search(path, command);
	if (dir)
		return (PATH_COMMAND);

	return (INVALID_COMMAND);
}

/**
 * get_func - selects the correct function
 * to execute
 * @command: the command to execute
 *
 * Return: pointer to the function that corresponds
 * to the function tha should be executed
 */
void (*get_func(char *command))(list_t *path, char **args)
{
	func_t funcs[] = {
		{"env", env},
		{"exit", handle_exit},
		{NULL, NULL}
	};
	int i = 0;

	while (i < 2)
	{
		if (_strcmp(command, funcs[i].command_name) == 0)
			return (funcs[i].func);
		i++;
	}

	return (NULL);
}
