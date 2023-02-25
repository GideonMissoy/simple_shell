#include "main.h"

/**
 * get_environ - returns the string array of our environ
 * @inf: Structure containing potential arguments.
 * Return: void
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}
	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment var
 * @inf: Structure containing potential arguments.
 * @var: string environ var property
 * Return: 1 on delete or 0 otherwise
 */
int _unsetenv(info_t *inf, char *var)
{
	list_t *nod = inf->env;
	size_t y = 0;
	char *d;

	if (!nod || !var)
		return (0);
	while (nod)
	{
		d = starts_with(nod->str, var);
		if (d && *d == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), y);
			y = 0;
			nod = inf->env;
			continue;
		}
		nod = nod->next;
		y++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify existing one
 * @inf: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: void
 */
int _setenv(info_t *inf, char *var, char *value)
{
	char *buff = NULL;
	list_t *nod;
	char *d;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	nod = inf->env;
	while (nod)
	{
		d = starts_with(nod->str, var);
		if (d && *d == '=')
		{
			free(nod->str);
			nod->str = buff;
			inf->env_changed = 1;
			return (0);
		}
		nod = nod->next;
	}
	add_node_end(&(inf->env), buff, 0);
	free(buff);
	inf->env_changed = 1;
	return (0);
}
