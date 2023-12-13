#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: The string whose length to check.
 *
 * Return: Integer length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	// Iterate through the string until the null terminator is reached
	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int _strcmp(char *s1, char *s2)
{
	// Iterate through both strings until null terminator is reached in either
	while (*s1 && *s2)
	{
		// Compare corresponding characters
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	// Check if both strings are equal
	if (*s1 == *s2)
		return (0);
	else
		// If not equal, return the difference between the first differing characters
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if needle starts with haystack.
 * @haystack: String to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	// Iterate through both strings until null terminator is reached in needle
	while (*needle)
		// If characters don't match, return NULL
		if (*needle++ != *haystack++)
			return (NULL);
	// If needle is found at the beginning of haystack, return the address of the next character
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	// Move dest pointer to the end of the string
	while (*dest)
		dest++;
	// Copy characters from src to dest
	while (*src)
		*dest++ = *src++;
	// Add null terminator to the concatenated string
	*dest = *src;
	return (ret);
}
