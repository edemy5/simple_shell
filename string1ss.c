#include "shell.h"

/**
 * _strcpys - copy a string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *_strcpys(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdups - duplicate a string
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdups(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _putsa - print input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _putsa(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchars(str[i]);
		i++;
	}
}

/**
 * _putchars - writes charac c to stdout
 * @c: The charac to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchars(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
