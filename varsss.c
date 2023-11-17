#include "shell.h"

/**
 * bis_chain - Test if current charac in buffer is a chain delimeter
 * @info: parameter struct
 * @buf: the charac buffer
 * @p: address of current positn in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int bis_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chains - checks we shd continue chaining basd on last status
 * @info: parameter struct
 * @buf: the charac buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chains(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_aliast - replaces an aliases in the tokenizd string
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_aliast(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_withs(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchrs(node->str, '=');
		if (!p)
			return (0);
		p = _strdups(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_varsa- replaces variables in the arg array
 * @info: pointer to the info struct
 * replace_strings: Replace a string in an array of strings
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_varsa(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmpl(info->argv[i], "$?"))
		{
			replace_strings(&(info->argv[i]),
					_strdups(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmpl(info->argv[i], "$$"))
		{
			replace_strings(&(info->argv[i]),
					_strdups(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_withs(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_strings(&(info->argv[i]),
					_strdups(_strchrs(node->str, '=') + 1));
			continue;
		}
		replace_strings(&info->argv[i], _strdups(""));

	}
	return (0);
}

/**
 * replace_strings - replace string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_strings(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

