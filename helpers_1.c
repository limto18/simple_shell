#include "main.h"

/**
 * arr_size - determine the lentgh
 * of the array
 * @str: the given string of strtow
 * @delim: delimeter
 *
 * Return: array size
 */
int arr_size(char *str, char *delim)
{
	int i = 0, size = 0;

	while (str[i])
	{
		while (str[i] == *delim)
			i++;
		if (str[i] != *delim && str[i])
		{
			size++;
			while (str[i] && str[i] != *delim)
				i++;
		}
	}
	return (size);
}

/**
* _split - splits a stirng into words
* @str: string to be splitted
* @delim: delimeter
*
* Return: pointer to the array of splitted words
*/
char **_split(char *str, char *delim)
{
	char **split, *token;
	int size = arr_size(str, delim), i = 0;

	if (size == 0)
		return (NULL);
	split = (char **) malloc(sizeof(char *) * (size + 1));

	if (!split)
		return (NULL);

	token = strtok(str, delim);
	while (token)
	{
		split[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	split[i] = NULL;
	return (split);
}
