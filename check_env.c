#include "main.h"

/**
 * check_env - checks if the typed variable is an env variable
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: void
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $
 * @h: head of the linked lidt
 * @in: input string
 * @st: last status of the shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int p, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (p = 0; in[p]; p++)
	{
		if (in[p] == '$')
		{
			if (in[p + 1] == '?')
				add_rvar_node(h, 2, st, lst), p++;
			else if (in[p + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), p++;
			else if (in[p + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[p + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[p + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[p + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[p + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + p, data);
		}
	}
	return (p);
}

/**
 * replaced_input - replaces string into variables
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string(replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int p, q, r;

	indx = *head;
	for (q = p = 0; p < nlen; p++)
	{
		if (input[q] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_inout[p] = input[q];
				q++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (r = 0; r < indx->len_var; r++)
					q++;
				p--;
			}
			else
			{
				for (r = 0; r < indx->len_val; r++)
				{
					new_input[p] = indx->val[r];
					p++;
				}
				q += (indx->len_var);
				p--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[p] = input[q];
			q++;
		}
	}
	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
