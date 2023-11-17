#include "shell.h"

/**
 * _myyhistory - Display the history list, one command per line,
 *              followed with line numbers, starting at 0.
 * @info: Structure that contains potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_lists(info->history);
	return (0);
}

/**
 * unset_aliase - Unset an alias.
 * @info: Parameter struct.
 * @str: The alias string to unset.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int unset_aliase(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchrs(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_indx(&(info->alias),
		get_node_indx(info->alias, node_starts_withs(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_aliase - Set an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias to set.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int set_aliase(info_t *info, char *str)
{
	char *p;

	p = _strchrs(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_aliase(info, str));

	unset_aliase(info, str);
	return (add_nodes_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_aliase - Print an alias string.
 * @node: The alias node to print.
 *
 * Return: Always return 0 on success, and 1 on error.
 */
int print_aliase(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchrs(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchars(*a);
		_putchars('\'');
		_putsa(p + 1);
		_putsa("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myaliase - Mimic the alias builtin (myaliase).
 * @info: Structure that contains potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int _myaliase(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_aliase(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchrs(info->argv[i], '=');
		if (p)
			set_aliase(info, info->argv[i]);
		else
			print_aliase(node_starts_withs(info->alias, info->argv[i], '='));
	}

	return (0);
}
