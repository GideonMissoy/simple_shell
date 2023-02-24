#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <stdarg.h>
#include <errno.h>

extern char **environ;

/**
 * struct fmt - types of data and their function
 * @ltr: the type of data
 * @type: pointer to function for type
 */
typedef struct fmt
{
	char *ltr;
	int (*type)();
} fmt;

void _puts(char *str);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int parse(char *line, int num_tokens, char *argv[], int failcount);
int exe(char *line, char **ar, char *nln, char **arry, char **argv, int flcnt);
void myfree(char *line, char **ar, char *newline, char **array);
int _strncmp(char *s1, char *s2, int len);
int checkbltin(char *line, char **ar, char *newline, char **array);
int numcount(char *line);
int searchpath(char *p, char **tokens);
int findonpath(char **tokens);
void executepath(char *p, char **tokens);
int _printf(const char *format, ...);
int chkfmt(va_list *args, const char *format, int i);
int prchr(va_list *args);
int prstr(va_list *args);
int prdgt(va_list *args);
void getdigits(int n);
int _putchar(char c);
void changedir(char **ar);

#endif
