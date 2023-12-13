#include "shell.h"

/**
 * hsh - Main shell loop.
 * @info: The parameter & return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	// Main shell loop
	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		// Display shell prompt if running interactively
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info); // Get user input
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info); // Find and execute built-in command
			if (builtin_ret == -1)
				find_cmd(info); // Find and execute external command
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0); // Free allocated memory in info struct
	}
	write_history(info); // Write command history to file
	free_info(info, 1); // Free remaining resources in info struct
	if (!interactive(info) && info->status)
		exit(info->status); // Exit with the status code if not interactive
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Finds a builtin command.
 * @info: The parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	// Iterate through the builtin table and execute the corresponding function
	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Finds a command in the PATH.
 * @info: The parameter & return info struct.
 *
 * Return: void.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	// Find the full path of the command in the PATH environment variable
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info); // Fork and execute the command
	}
	else
	{
		// If the command is not found, print an error message
		if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info); // Fork and execute the command
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks a child process to run a command.
 * @info: The parameter & return info struct.
 *
 * Return: void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	// Fork a child process
	child_pid = fork();
	if (child_pid == -1)
	{
		// Handle fork error
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		// In the child process, execute the command
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		// In the parent process, wait for the child to complete
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			// Update status with the exit status of the child
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
