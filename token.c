#include "shell.h"

/**
 * parse - function to convert user input to tokens
 * @line: input to be parsed
 * @num_tokens: number of tokens
 * @argv: array of arguments
 * @cmdcount: number of commands that have been entered
 * Return: return 0 upon sucess
 */
int parse(char *line, int num_tokens, char **argv, int cmdcount)
{
	int i = 0, bltin, exval = 0;
	char *p = NULL, *newline = NULL, **array = NULL, **ar = NULL;
	char *del = " \t\r\n\f\v";

	array = malloc(sizeof(char *) * num_tokens); /* creates array to store tokens */

	newline = _strdup(line); /* duplicates line so we can strtok */

	p = strtok(newline, del); /* points to beginning of first token before any delimeter char*/

	if (p == NULL)
	{
		/* if line does not exist after strtok, doesn't contiue*/
		myfree(line, ar, newline, array);
		return (0);
	}

	/* it continues getting the tokens, then stores a pointer to in array */
	for (; p != NULL; p = strtok(NULL, del))
		array[i++] = p;

	/* creates an array execve can use */
	ar = malloc(sizeof(char *) * (num_tokens + 1));

	/* duplicates the input strings into the new array */
	for (i = 0; i < num_tokens; i++)
		ar[i] = _strdup(array[i]);

	ar[i] = NULL; /* null terminates the array */

	bltin = checkbltin(line, ar, newline, array); /* checks for built-ins */

	if (bltin == 0) /* if not a built-in passes into exe */
		exval = exe(line, ar, newline, array, argv, cmdcount);

	myfree(line, ar, newline, array);

	return (exval); /* returns whether or not execve failed or worked */
}

/**
 * myfree - function to free memory
 * @line: line to be freed
 * @ar: array to be freed
 * @newline: line to be freed
 * @array: array to be freed
 */
void myfree(char *line, char **ar, char *newline, char **array)
{
	int i = 0;

	if (ar != NULL)
	{
		while (ar[i] != NULL)
		{
			free(ar[i]);
			i++;
		}
		free(ar);
	}

	if (newline != NULL)
		free(newline);

	if (line != NULL)
		free(line);

	if (array != NULL)
		free(array);
}
