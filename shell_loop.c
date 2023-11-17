#include "shell.h"

/**
 * hsh - main shell loop
 * @info: parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (myinteractive(info))
			_putsa("$ ");
		_eputchare(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_infoi(info, av);
			builtin_ret = find_builtinc(info);
			if (builtin_ret == -1)
				find_cmdp(info);
		}
		else if (myinteractive(info))
			_putchars('\n');
		free_infof(info, 0);
	}
	write_historycf(info);
	free_infof(info, 1);
	if (!myinteractive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtinc - find a builtin commnd
 * @info: parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exits()
 */
int find_builtinc(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exits", _myexits},
		{"env", _myenvp},
		{"help", _myhelpp},
		{"history", _myhistory},
		{"setenv", _mysetenve},
		{"unsetenv", _myunsetenvr},
		{"cd", _mycdd},
		{"alias", _myaliase},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmpl(info->argv[0], builtintbl[i].type) == 0)
		{
			info->linecountnw++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmdp- find a commnd in PATH
 * @info: parameter & return info struct
 *
 * Return: void
 */
void find_cmdp(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->linecountnw++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_mydelim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenvp(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmde(info);
	}
	else
	{
		if ((myinteractive(info) || _getenvp(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmde(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_errorm(info, "not found\n");
		}
	}
}

/**
 * fork_cmde - fork a an exec thread to run cmd
 * @info: parameter & return info struct
 *
 * Return: void
 */
void fork_cmde(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_infof(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_errorm(info, "Permission denied\n");
		}
	}
}

