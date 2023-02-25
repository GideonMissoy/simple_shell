#include "shell.h"

/**
 * _puts - functiont to write strinng to standard out
 * @str: string to write
 */
void _puts(char *str)
{
	while (*str  != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

/**
 * prstr - prints strings from arg
 * @args: argument pointer
 *
 * Return: count of string elements printed
 */
int prstr(va_list *args)
{
	int p = 0;
	char *ar;

	ar = va_arg(*args, char *);

	while (*ar != '\0')
	{
		_putchar(*ar);
		p++;
		ar++;
	}
	return (p);
}

/**
 * _putchar - writes the character c to sterr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(2, &c, 1));
}
