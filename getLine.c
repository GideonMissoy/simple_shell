#include "main.h"

/**
 * input_buf - buffers chained commands
 * @inf: parameter struct
 * @buff: address of buffer
 * @ln: address of len var
 *
 * Return: void
 */
ssize_t input_buf(info_t *inf, char **buff, size_t *ln)
{
	ssize_t k = 0;
	size_t len_p = 0;

	if (!*ln) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)inf->cmd_buf);*/
		free(*buff);
			*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		k = getline(buff, &len_p, stdin);
#else
		k = _getline(inf, buff, &len_p);
#endif
		if (k > 0)
		{
			if ((*buff)[k - 1] == '\n')
			{
				(*buff)[k - 1] = '\0'; /* remove trailing newline */
				k--;
			}
			inf->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(inf, *buff, inf->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*ln = k;
				inf->cmd_buf = buff;
			}
		}
	}
	return (k);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 * Return: void
 */
ssize_t get_input(info_t *inf)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t y, g, len;
	ssize_t k = 0;
	char **buf_p = &(inf->arg), *d;

	_putchar(BUF_FLUSH);
	_putchar(BUF_FLUSH);
	k = input_buf(inf, &buff, &len);
	if (k == -1) /* EOF */
		return (-1);
	if (len)        /* we have commands left in the chain buffer */
	{
		g = y; /* init new iterator to current buff position */
		d = buff + y; /* get pointer for return */
		check_chain(inf, buff, &g, y, len);
		while (g < len) /* iterate to semicolon or end */
		{
			if (is_chain(inf, buff, &g))
				break;
			g++;
		}
		y = g + 1; /* increment past nulled ';'' */
		if (y >= len) /* reached end of buffer? */
		{
			y = len = 0; /* reset position and length */
			inf->cmd_buf_type = CMD_NORM;
		}
		*buf_p = d; /* pass back pointer to current command position */
		return (_strlen(d)); /* return length of current command */
	}
	*buf_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (k); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @inf: parameter struct
 * @buff: buffer
 * @y: size
 *
 * Return: void
 */
ssize_t read_buf(info_t *inf, char *buff, size_t *y)
{
	ssize_t k = 0;

	if (*y)
		return (0);
	k = read(inf->readfd, buff, READ_BUF_SIZE);
	if (k >= 0)
		*y = k;
	return (k);
}

/**
 * _getline - gets next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: void
 */
int _getline(info_t *inf, char **ptr, size_t *len)
{
	static char buff[READ_BUF_SIZE];
	static size_t y, ln;
	size_t k;
	ssize_t r = 0, h = 0;
	char *d = NULL, *new_d = NULL, *c;

	d = *ptr;
	if (d && len)
		h = *len;
	if (y == ln)
		y = ln = 0;
	r = read_buf(inf, buff, &ln);
	if (r == -1 || (r == 0 && ln == 0))
		return (-1);
	c = _strchr(buff + y, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : ln;
	new_d = _realloc(d, h, h ? h + k : k + 1);
	if (!new_d) /* MALLOC FAILURE! */
		return (d ? free(d), -1 : -1);
	if (h)
		_strncat(new_d, buff + y, k - y);
	else
		_strncpy(new_d, buff + y, k - y + 1);
	h += k - y;
	y = k;
	d = new_d;
	if (len)
		*len = h;
	*ptr = d;
	return (h);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
