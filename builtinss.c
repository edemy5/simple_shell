#include "shell.h"

/**
 * _myexits - Exit the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int _myexits(info_t *info)
{
	int exitscheck;

	if (info->argv[1]) /* If there is an exits argument */
	{
		exitscheck = _erratoinew(info->argv[1]);
		if (exitscheck == -1)
		{
			info->status = 2;
			print_errorm(info, "Illegal number: ");
			_eputsa(info->argv[1]);
			_eputchare('\n');
			return (1);
		}
		info->err_num = _erratoinew(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycdd- Change the current directory.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _mycdd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_putsa("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenvp(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenvp(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmpl(info->argv[1], "-") == 0)
	{
		if (!_getenvp(info, "OLDPWD="))
		{
			_putsa(s);
			_putchars('\n');
			return (1);
		}
		_putsa(_getenvp(info, "OLDPWD=")), _putchars('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenvp(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_errorm(info, "can't cd to ");
		_eputsa(info->argv[1]), _eputchare('\n');
	}
	else
	{
		_setenvi(info, "OLDPWD", _getenvp(info, "PWD="));
		_setenvi(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelpp - Display help information.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myhelpp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_putsa("help call works. Function not yet implemented \n");
	if (0)
		_putsa(*arg_array); /* Temporarily unused workaround */
	return (0);
}
