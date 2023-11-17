#include "shell.h"

/**
 * get_history_files - gets history file
 * @info: parametr struct
 *
 * Return: allocatd string containing history file
 */
char *get_history_files(info_t *info)
{
	char *buf, *dir;

	dir = _getenvp(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpys(buf, dir);
	_strcats(buf, "/");
	_strcats(buf, HIST_FILE);
	return (buf);
}

/**
 * write_historycf - create a file, or append to existing file
 * @info: parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_historycf(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_files(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		my_putsfd(node->str, fd);
		_putfdc('\n', fd);
	}
	_putfdc(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_historyf - read file history
 * @info: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_historyf(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_files(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_lists(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_lists(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_indx(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_lists - add entry to history linkd list
 * @info: Structure containing potential argumnt. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_lists(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_nodes_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_historycg - renumbers the history linkd list after changs
 * @info: Structure containing potential argument. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_historycg(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
