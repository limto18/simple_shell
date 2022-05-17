#include "main.h"

/**
 * main - the main entry of the shell
 * @argc: the number of arguments
 * @argv: array of arguments.
 * Return: exit code
 */
int main(int argc __attribute__((unused)), char **argv)
{
	list_t *path = NULL;

	path = init_path(&path);
	if (!isatty(STDIN_FILENO))
	{
		non_interactive(path, argv[0]);
	}
	else
	{
		interactive(path, argv[0]);
	}
	free_list(path);
	exit(0);
}
