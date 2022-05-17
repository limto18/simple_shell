#include "main.h"

/**
 * _getline - this function handle
 * line reading
 * @line: the address of the line
 * @mode: is interactive or non-interactive
 * Description -
 *				INTERACTIVE (1)
 *				NON-INTERACTIVE (0)
 *
 * Return: on success the number of
 * caracteres read, on fails -1
 */
ssize_t _getline(char **line, int mode)
{
	ssize_t ret;
	size_t n = 0;

	if (mode)
		printf("($) ");

	ret = getline(line, &n, stdin);

	return (ret);
}

/**
 * _execve - execute the command
 * @path: list of command directory
 * @args: the array of argument to execute
 * @command_type: the command_type
 */
void _execve(list_t *path, char **args, int command_type)
{
	pid_t pid;
	int status;

	if (command_type == EXTERNAL_COMMAND || command_type == PATH_COMMAND)
	{
		pid = fork();
		if (pid == 0)
		{
			execute_command(path, args, command_type);
		}
		else
			waitpid(pid, &status, 0);
	}
	else if (command_type == INTERNAL_COMMAND)
		execute_command(path, args, command_type);
}

/**
 * execute_command - execute the command
 * @path: list of command directory
 * @args: the array of argument to execute
 * @command_type: the command_type
 */
void execute_command(list_t *path, char **args, int command_type)
{
	void (*func)(list_t *path, char **args);

	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror(args[0]);
			exit(2);
		}
	}

	if (command_type == PATH_COMMAND)
	{
		if (execve(_search(path, args[0]), args, NULL) == -1)
		{
			perror(args[0]);
			exit(2);
		}
	}
	if (command_type == INTERNAL_COMMAND)
	{
		func = get_func(args[0]);
		func(path, args);
	}
}

/**
 * non_interactive - the function handle the
 * non-interactive mode off the shell
 * @path: list of command directory
 * @shell_name: the name of the shell
 */
void non_interactive(list_t *path, char *shell_name)
{
	char *cmd, *line, delim = '\n', **lines, **args;
	int i = 1, command_type;

	while (_getline(&line, NON_INTERACTIVE_MODE) != -1)
	{
		/* remove new line */
		cmd = strtok(line, &delim);
		while (cmd)
		{
			lines = _split(cmd, ";");
			args = _split(lines[0], " ");
			command_type = get_command_type(path, args[0]);

			if (command_type == INVALID_COMMAND)
				print_error(shell_name, args[0], i, NON_INTERACTIVE_MODE);

			_execve(path, args, command_type);
			free(args);
			free(lines);
			i++;
			cmd = strtok(NULL, &delim);
		}
	}
	free(line);
}


/**
 * interactive - the function handle the
 * interactive mode off the shell
 * @path: list of command directory
 * @shell_name: the name of the shell
 */
void interactive(list_t *path, char *shell_name)
{
	char *line, delim = '\n', **args;
	ssize_t read = 0;
	int command_type;

	while (1)
	{
		read = _getline(&line, INTERACTIVE_MODE);
		if (read > 1)
		{
			/* remove new line */
			strtok(line, &delim);
			args = _split(line, " ");

			command_type = get_command_type(path, args[0]);

			if (command_type == INVALID_COMMAND)
				print_error(shell_name, args[0], 0, INTERACTIVE_MODE);

			_execve(path, args, command_type);
			free(args);
		}
		
		if (read == -1)
			break;
	}
	free(line);
}
