#include "shell.h"

/**
 * clear_infos - initializes info_t struct
 * @info: a struct address
 */
void clear_infos(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_infoi - initializes info_t struct
 * @info: a struct address
 * @av: an argument vector
 */
void set_infoi(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtows(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdups(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_aliast(info);
		replace_varsa(info);
	}
}

/**
 * free_infof - frees info_t struct fields
 * @info: a struct address
 * @all: true if freeing all fields
 */
void free_infof(info_t *info, int all)
{
	ffreess(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_lists(&(info->env));
		if (info->history)
			free_lists(&(info->history));
		if (info->alias)
			free_lists(&(info->alias));
		ffreess(info->environ);
		info->environ = NULL;
		freeptr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchars(BUF_FLUSH);
	}
}
