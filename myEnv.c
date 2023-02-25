#include "main.h"

/**
 * _myenv - prints the current environment
 * @inf: Structure containing potential arguments.
 * Return: void
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}
/**
 * _getenv - gets value of environ variable
 * @inf: Structure containing potential arguments.
 * @nam: env var name
 * Return: void
 */
char *_getenv(info_t *inf, const char *nam)
{
	list_t *node = inf->env;
	char *d;

	while (node)
	{
		d = starts_with(node->str, nam);
			if (d && *d)
				return (d);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment var
 *             or modify an existing one
 * @inf: Structure containing potential arguments
 *  Return: void
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment var
 * @inf: Structure containing potential arguments.
 *  Return: void
 */
int _myunsetenv(info_t *inf)
{
	int y;

	if (inf->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (y = 1; y <= inf->argc; y++)
		_unsetenv(inf, inf->argv[y]);
	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @inf: Structure containing potential arguments.
 * Return: void
 */
int populate_env_list(info_t *inf)
{
	list_t *node = NULL;
	size_t y;

	for (y = 0; environ[y]; y++)
		add_node_end(&node, environ[y], 0);
	inf->env = node;
	return (0);
}
