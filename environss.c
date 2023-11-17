#include "shell.h"

/**
 * _myenvp - Print the current environment.
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always return 0.
 */
int _myenvp(info_t *info)
{
	print_lists_strel(info->env);
	return (0);
}

/**
 * _getenvp - Get the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: Return the value or NULL if not found.
 */
char *_getenvp(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_withs(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenve - Initialize a new environment variable
 *             or modify an existing one.
 * @info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int _mysetenve(info_t *info)
{
	if (info->argc != 3)
	{
		_eputsa("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenvi(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenvr - Remove an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int _myunsetenvr(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputsa("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenva(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_listt - Populate the env linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always return 0.
 */
int populate_env_listt(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nodes_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
