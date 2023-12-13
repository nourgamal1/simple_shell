#include "shell.h"

/**
 * bfree - Frees a pointer and NULLs the address.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	// Check if the pointer and the content it points to exist
	if (ptr && *ptr)
	{
		// Free the memory and set the pointer to NULL
		free(*ptr);
		*ptr = NULL;
		return (1); // Return 1 indicating successful freeing
	}
	return (0); // Return 0 indicating that nothing was freed
}
