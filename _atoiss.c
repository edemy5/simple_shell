#include "shell.h"

/**
 * myinteractive - returns true if the shell is in myinteractive mode
 * @info: pointer to the struct containing shell info
 *
 * This function checks if the standard input is a terminal and if the read
 * file descriptor is within valid limits.
 *
 * Return: 1 if in myinteractive mode, 0 otherwise
 */
int myinteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_mydelim - checks if the character is a delimiter
 * @c: the char to check
 * @mydelim: the delimiter string to compare against
 * Return: 1 if true, otherwise return 0.
 */
int is_mydelim(char c, char *mydelim)
{

/* Iterate through the mydelimiter string and compare each character with 'c' */

	while (*mydelim)
		if (*mydelim++ == c)
			return (1);
	return (0);
}

/**
 * _myisalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, return 0 if otherwise.
 */

int _myisalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoinw - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoinw(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
