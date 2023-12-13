#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info; // Unused parameter (info)
	
	// Check if the path is not NULL and retrieve file status
	if (!path || stat(path, &st))
		return (0); // If path is NULL or stat fails, return 0

	// Check if the file is a regular file
	if (st.st_mode & S_IFREG)
	{
		return (1); // Return 1 if it's a regular file (executable)
	}
	return (0); // Return 0 otherwise
}

/**
 * dup_chars - Duplicates characters.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024]; // Static buffer to store duplicated characters
	int i = 0, k = 0;

	// Iterate over the characters in the specified range
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0; // Null-terminate the buffer
	return (buf); // Return the pointer to the buffer
}

/**
 * find_path - Finds the cmd in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	// Check if cmd starts with "./" and is an executable command
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	// Iterate over the characters in the PATH string
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			// Duplicate characters from curr_pos to i in the PATH string
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			// Check if the concatenated path is an executable command
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL); // Return NULL if the cmd is not found in the PATH string
}
