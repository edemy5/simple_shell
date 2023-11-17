#include "shell.h"

/**
 * _eputsa - prints a string to the standard error stream
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputsa(char *str)
{
	int i = 0;
/* Check of the input string is null */

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchare(str[i]);
		i++;
	}
}

/**
 * _eputchare - writes the character to the standard error stream
 * @c: The character to print
 *
 * Return: On success 1, on error, return -1, and errno is set appropriately.
 */
int _eputchare(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfdc - writes the character to the specified file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1, return -1 on error, and errno is set appropriately.
 */
int _putfdc(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * my_putsfd - prints a string to the specified file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int my_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfdc(*str++, fd);
	}
	return (i);
}
