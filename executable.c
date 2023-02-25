#include "main.h"

/**
 * is_cmd - determines if a file is an executable command
 * @inf: the info struct
 * @pth: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *inf, char *pth)
{
	struct stat st;

	(void)inf;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pthstr: the PATH string
 * @strt: starting index
 * @stp: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pthstr, int strt, int stp)
{
	static char buf[1024];
	int y = 0, f = 0;

	for (f = 0, y = strt; y < stp; y++)
		if (pthstr[y] != ':')
			buf[f++] = pthstr[y];
	buf[f] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inf: the info struct
 * @pthstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *inf, char *pthstr, char *cmd)
{
	int y = 0, curr_pos = 0;
	char *pth;

	if (!pthstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pthstr[y] || pthstr[y] == ':')
		{
			pth = dup_chars(pthstr, curr_pos, y);
			if (!*pth)
				_strcat(pth, cmd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cmd);
			}
			if (is_cmd(inf, pth))
				return (pth);
			if (!pthstr[y])
				break;
			curr_pos = y;
		}
		y++;
	}
	return (NULL);
}
