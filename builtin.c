#include "shell.h"

/**
 * checkbltin - checks if the command entered is a built-in
 * @line: input entered by user
 * @ar: array that can be handled by execve
 * @newline: duplicate of line
 * @array: Tokens to check
 * Return: Return depends upon if the built-in was found
 */
int checkbltin(char *line, char **ar, char *newline, char **array)
{
	int i = 0;

	if (_strcmp(ar[0], "exit") == 0)
	{
		myfree(line, ar, newline, array);
		_exit(errno);
	}

	if (_strcmp(ar[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			_puts(environ[i]);
			write(1, "\n", 1);
		}
		return (2);
	}

	if (_strcmp(ar[0], "cd") == 0)
	{
		changedir(ar);
		return (2);
	}

	return (0);
}


/**
 * changedir - changes directory to ar
 * @ar: the directory to change to or nothing
 */
void changedir(char **ar)
{
	int i = 0;
	char *homeval = NULL, *home = NULL;

	if (ar[1] == NULL)
	{ /* if cd is by itself */
		for (i = 0; environ[i] != NULL; i++) /* loops through environ */
		{
			if (_strncmp("HOME=", environ[i], 5) == 0)
			{ /* find the line matching home */
				home = _strdup(environ[i]);
				strtok(home, "="); /* stores its value */
				homeval = strtok(NULL, "=");
				break;
			}
		}
	}
	else
		homeval = ar[1]; /* homeval is set to 2nd arg */
	chdir(homeval); /* change directory to homeval */
	free(home);
}
