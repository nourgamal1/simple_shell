#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest: The destination.
 * @src: The source.
 *
 * Return: Pointer to destination.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	// Check for self-copy or null source
	if (dest == src || src == 0)
		return (dest);

	// Copy characters from source to destination
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	// Add null terminator to the copied string
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	// Check for null input string
	if (str == NULL)
		return (NULL);

	// Calculate the length of the input string
	while (*str++)
		length++;

	// Allocate memory for the duplicated string
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	// Copy characters from the input string to the duplicated string
	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * _puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int i = 0;

	// Check for null input string
	if (!str)
		return;

	// Print each character of the string
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	// Check for buffer flush or buffer size limit
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	// If not flushing, add character to the buffer
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
