#include "main.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @d: address of current position in buff
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *inf, char *buff, size_t *d)
{
	size_t g = *d;

	if (buff[g] == '|' && buff[g + 1] == '|')
	{
		buff[g] = 0;
		g++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[g] == '&' && buff[g + 1] == '&')
	{
		buff[g] = 0;
		g++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[g] == ';') /* found end of this command */
	{
		buff[g] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*d = g;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @d: address of current position in buf
 * @y: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *buff, size_t *d, size_t y, size_t len)
{
	size_t g = *d;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[y] = 0;
			g = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[y] = 0;
			g = len;
		}
	}

	*d = g;
}

/**
 * replace_alias - replaces aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *inf)
{
	int y;
	list_t *node;
	char *d;

	for (y = 0; y < 10; y++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		d = _strchr(node->str, '=');
		if (!d)
			return (0);
		d = _strdup(d + 1);
		if (!d)
			return (0);
		inf->argv[0] = d;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *inf)
{
	int y = 0;
	list_t *node;

	for (y = 0; inf->argv[y]; y++)
	{
		if (inf->argv[y][0] != '$' || !inf->argv[y][1])
			continue;

		if (!_strcmp(inf->argv[y], "$?"))
		{
			replace_string(&(inf->argv[y]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[y], "$$"))
		{
			replace_string(&(inf->argv[y]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[y][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[y]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[y], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @oldstr: address of old string
 * @newstr: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
