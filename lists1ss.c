#include "shell.h"

/**
 * list_lend - length of linked list is determined
 * @h: pointer to first node
 *
 * Return: size of the list
 */
size_t list_lend(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * listar_to_strings - returns array of strings from the list->str
 * @head: pointer to first node
 *
 * Return: array of strngs
 */
char **listar_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_lend(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpys(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_lists - print elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of the list
 */
size_t print_lists(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_putsa(convert_number(h->num, 10, 0));
		_putchars(':');
		_putchars(' ');
		_putsa(h->str ? h->str : "(nil)");
		_putsa("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_withs - returns node whose string begins with a prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *node_starts_withs(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_withs(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_indx - get index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_indx(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

