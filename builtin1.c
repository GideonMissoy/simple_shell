#include "main.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing potential arguments.
 *  Return: void
 */
int _myhistory(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter structure
 * @str: the string
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *inf, char *str)
{
	char *d, h;
	int rt;

	d = _strchr(str, '=');
	if (!d)
		return (1);
	h = *d;
	*d = 0;
	rt = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, str, -1)));
	*d = h;
	return (rt);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter structure
 * @str: the string alias
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *inf, char *str)
{
	char *d;

	d = _strchr(str, '=');
	if (!d)
		return (1);
	if (!*++d)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nod: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *nod)
{
	char *d = NULL, *b = NULL;

	if (nod)
	{
		d = _strchr(nod->str, '=');
		for (b = nod->str; b <= d; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(d + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin man alias
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myalias(info_t *inf)
{
	int y = 0;
	char *d = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (y = 1; inf->argv[y]; y++)
	{
		d = _strchr(inf->argv[y], '=');
		if (d)
			set_alias(inf, inf->argv[y]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[y], '='));
	}

	return (0);
}
