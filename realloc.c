#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The number of bytes to be filled.
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	// Iterate over the memory area and fill it with the constant byte 'b'
	for (i = 0; i < n; i++)
		s[i] = b;
	return (s); // Return a pointer to the memory area s
}

/**
 * ffree - Frees a string of strings.
 * @pp: String of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	// Check if pp is not NULL
	if (!pp)
		return;

	// Free each string in the array
	while (*pp)
		free(*pp++);
	
	free(a); // Free the array itself
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the old block or a new block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	// If ptr is NULL, allocate a new block of size new_size
	if (!ptr)
		return (malloc(new_size));

	// If new_size is 0, free the previous block and return NULL
	if (!new_size)
		return (free(ptr), NULL);

	// If new_size is equal to old_size, return the original pointer
	if (new_size == old_size)
		return (ptr);

	// Allocate a new block of size new_size
	p = malloc(new_size);

	// If malloc fails, return NULL
	if (!p)
		return (NULL);

	// Copy the contents of the old block to the new block
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	// Free the old block
	free(ptr);

	// Return a pointer to the new block
	return (p);
}
