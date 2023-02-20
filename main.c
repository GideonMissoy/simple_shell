#include "main.h"
/**
 * free_data - frees data structures
 * @datash: data structure
 * Return: no return
 */
void free_data(data_shell *datash)
{
	unsigned int p;

	for (p = 0; datash->_environ[p]; p++)
		free(datash->_environ[p]);

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure
 * @datash: data structure
 * @av: argument vector
 * Return: 0
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int p;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (p = 0; environ[p]; p++)
		;

	datash->_environ = malloc(sizeof(char *) * (p + 1));

	for (p = 0; environ[p]; p++)
		datash->_environ[p] = _strdup(environ[p]);

	datash->_environ[p] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
