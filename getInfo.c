#include "main.h"

/**
 * clear_info - initializes info_t struct
 * @inf: struct address
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @inf: struct address
 * @agv: argument vector
 */
void set_info(info_t *inf, char **agv)
{
	int y = 0;

	inf->fname = agv[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (y = 0; inf->argv && inf->argv[y]; y++)
			inf->argc = y;
		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * free_info - frees info_t struct fields
 * @inf: struct address
 * @al: true if freeing all fields
 */
void free_info(info_t *inf, int al)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (al)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
		inf->environ = NULL;
		bfree((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}
