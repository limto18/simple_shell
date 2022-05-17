#include "main.h"

/**
 * print_number - print number
 * @n: number to print
 * @stream: stream to print out
 */
void print_number(int n, int stream)
{
	char c = (n % 10) + '0';

	if (n > 9)
		print_number(n / 10, stream);
	write(stream, &c, 1);
}

/**
 * print_error - this function print error
 * @shell_name: the name of the shell
 * @command: the command is entered by the user
 * @line: the line where the command is not good
 * @mode: is interactive or non-interactive
 * Description -
 *				INTERACTIVE (1)
 *				NON-INTERACTIVE (0)
 */
void print_error(char *shell_name, char *command,
int line __attribute__((unused)), int mode)
{
	print(shell_name, STDERR_FILENO);
	print(": ", STDERR_FILENO);
	if (!mode)
	{
		print_number(line, STDERR_FILENO);
		print(": ", STDERR_FILENO);
	}
	print(command, STDERR_FILENO);
	print(": not found\n", STDERR_FILENO);
}

/**
 * print - print message
 * @str: string to print
 * @stream: stream to print out
 */
void print(char *str, int stream)
{
	int i = 0;

	for (; str[i]; i++)
		write(stream, &str[i], 1);
}
