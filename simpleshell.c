#include "main.h"

/**
 * interactive - returns true if shell is communicatting
 * @sa: struct address
 *
 * Return: 1 if communicatting
 */
int interactive(info_t *sa)
{
	return (isatty(STDIN_FILENO) && sa->readfd <= 2);
}

/**
 * is_delim - check if character is  delimeter
 * @s: the char to look for
 * @str: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char s, char *str)
{
	while (*str)
		if (*str++ == s)
			return (1);
		else
			return (0);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@s: character to input
 *Return: 1 if s is alphabetic, 0 otherwise
 */

int _isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an int
 *@s: the string to be converted
 *Return: 0 if no numbers in string else converted number otherwise
 */

int _atoi(char *s)
{
	int y, in = 1, flag = 0, outpt;
	unsigned int rst = 0;

	for (y = 0;  s[y] != '\0' && flag != 2; y++)
	{
		if (s[y] == '-')
			in *= -1;

		if (s[y] >= '0' && s[y] <= '9')
		{
			flag = 1;
			rst *= 10;
			rst += (s[y] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (in == -1)
		outpt = -rst;
	else
		outpt = rst;

	return (outpt);
}
