#include "main.h"

/**
 * _strlen - returns the length of a string.
 * @s: string whose length should be return
 *
 * Return: (int) the length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;

	return (i);
}

/**
 * _strcat - concatenates two strings.
 * @dest: destination.
 * @src: source
 *
 * Return: pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
	int len = _strlen(dest);

	do {
		dest[len] = *src;
		len++;
	} while (*src++);

	dest[len] = '\0';

	return (dest);
}

/**
 * _strchr - locates a character in a string.
 * @s: source
 * @c: char to find
 *
 * Return: a pointer to the first occurrence of
 * the character c in the string s, or NULL if
 * the character is not found.
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] != '\0' && s[i] != c)
		i++;

	if (s[i] == c)
		return (s + i);
	return (NULL);
}

/**
 * _strcmp - compares two strings.
 * @s1: first string.
 * @s2: second string.
 *
 * Return: an integer less than,
 * equal to, or greater than zero
 * if s1 is found
 */
int _strcmp(char *s1, char *s2)
{
	int comp = 0, i = 0;

	while (1)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			break;
		else if (s1[i] == '\0')
		{
			comp = s2[i];
			break;
		}
		else if (s2[i] == '\0')
		{
			comp = s1[i];
			break;
		}
		else if (s1[i] != s2[i])
		{
			comp = s1[i] - s2[i];
			break;
		}
		else
			i++;

	}

	return (comp);
}
