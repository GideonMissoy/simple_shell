#include "main.h"

/**
 * _myexit - exits the shell
 * @inf: Structure containing arguments for maintain
 *          constant function prototype.
 * Return: void
 */
int _myexit(info_t *inf)
{
	int excheck;

	if (inf->argv[1])  /* If there is an exit arg */
	{
		excheck = _erratoi(inf->argv[1]);
		if (excheck == -1)
		{
			inf->status = 2;
			print_error(inf, "Error number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @inf: Structure containing potential arguments.
 * Return: void
 */
int _mycd(info_t *inf)
{
	char *c, *dr, buffer[1024];
	int rt;

	c = getcwd(buffer, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dr = _getenv(inf, "HOME=");
		if (!dr)
			rt = /* TODO: what should this be? */
				chdir((dr = _getenv(inf, "PWD=")) ? dr : "/");
		else
			rt = chdir(dr);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		rt = /* TODO: what should this be? */
			chdir((dr = _getenv(inf, "OLDPWD=")) ? dr : "/");
	}
	else
		rt = chdir(inf->argv[1]);
	if (rt == -1)
	{
		print_error(inf, "can not cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - change current directory of the process
 * @inf: Structure containing potential arguments.
 *  Return: void
 */
int _myhelp(info_t *inf)
{
	char **ray;
		ray = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ray); /* temp att_unused workaround */
	return (0);
}
