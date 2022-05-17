#include "main.h"

/**
 * add_node_end - adds a new node at the beginning
 * of a list_t list.
 * @head: the head of the list
 * @str: the value of the head
 *
 * Return: the pointer to the new node.
 */
list_t *add_node_end(list_t **head, char *str)
{
	list_t *new, *list;

	list = *head;
	new = malloc(sizeof(list_t));

	if (!new)
		return (new);

	new->len = _strlen(str);
	new->str = malloc(sizeof(char) * new->len);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}

	_strcat(new->str, str);
	new->next = NULL;

	if (*head == NULL)
		*head = new;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}

	return (*head);
}

/**
 * free_list - frees a list_t list.
 * @head: the head list to frees
 */
void free_list(list_t *head)
{
	list_t *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

/**
 * init_path - create a linked list
 * of path contain in the env
 * @head: the head of the list
 *
 * Return: A pointer to the list
 */
list_t *init_path(list_t **head)
{
	char  **path;
	int i = 0;

	path = _split(getenv("PATH"), ":");
	*head = add_node_end(head, "./");

	while (path[i])
	{
		*head = add_node_end(head, path[i]);
		i++;
	}

	free(path);
	return (*head);
}

/**
 * _search - this function search a command
 * in the list of directory
 * @path: the list of the path
 * @str: the command file to search
 *
 * Return: Null if failed, else the concatenation
 * of the directory and the command.
 */
char *_search(list_t *path, char *str)
{
	struct stat st;
	list_t *list = path;
	char cmd[1000] = {0}, *cwd = NULL;
	int found = 0;

	cwd = getcwd(cwd, 0);
	while (list)
	{
		chdir(list->str);
		if (stat(str, &st) == 0)
		{
			/* concatenation of the path and the command */
			_strcat(cmd, list->str);
			_strcat(cmd, "/");
			str = _strcat(cmd, str);
			found = 1;
			break;
		}
		list = list->next;
	}
	chdir(cwd);
	if (found)
		return (str);
	return (NULL);
}
