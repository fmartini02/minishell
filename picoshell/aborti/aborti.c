/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aborti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:14:11 by fmartini          #+#    #+#             */
/*   Updated: 2024/05/01 15:54:19 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main()
{
	// Command and arguments for each command
	char *cmd1[] = {"cmd1", "args1", NULL};
	char *cmd2[] = {"cmd2", "args2", NULL};
	char *cmd3[] = {"cmd3", "args3", NULL};
	char *cmd4[] = {"cmd4", "args4", NULL};

	// Array of commands
	char **cmds[] = {cmd1, cmd2, cmd3, cmd4};
	// Number of commands
	int num_cmds = sizeof(cmds) / sizeof(cmds[0]);
	// Pipes
	int pipes[num_cmds - 1][2];
	// Create pipes
	int i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipes[i]) == -1) {
			perror("Pipe failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// Fork processes
	i = 0;
	while (i < num_cmds)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)// Child process
		{
			// If not the first command, connect input to the previous pipe
			if (i != 0)
			{
				if (dup2(pipes[i - 1][READ_END], STDIN_FILENO) == -1)
				{
					perror("Dup2 failed");
					exit(EXIT_FAILURE);
				}
				// Close the read end of the previous pipe
				close(pipes[i - 1][READ_END]);
			}
			// If not the last command, connect output to the current pipe
			if (i != num_cmds - 1)
			{
				if (dup2(pipes[i][WRITE_END], STDOUT_FILENO) == -1)
				{
					perror("Dup2 failed");
					exit(EXIT_FAILURE);
				}
				// Close the write end of the current pipe
				close(pipes[i][WRITE_END]);
			}
		// Execute command
			execvp(cmds[i][0], cmds[i]);//closing child process
			perror("Execvp failed");
			exit(EXIT_FAILURE);
		}
		i++;//incrementing for new child process
	}
	// Close all pipe ends in the parent process
	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipes[i][READ_END]);
		close(pipes[i][WRITE_END]);
		i++;
	}
	// Wait for all child processes to finish
	i = 0;
	while (i < num_cmds)
	{
		wait(NULL);
		i++;
	}
	return 0;
}

char *const	*ft_exec_args(char *path, char *args)
{
	int				i;
	int				y;
	int				j;
	char *const		*exec_args;
	char			*tmp;

	i = j = y = 0;
	exec_args = exec_args = malloc(sizeof(char *) * (ft_count_words((const char *)args) + 2));//+2 (path + null)
	tmp = malloc (sizeof(char) * (ft_strlen_till_char(path, i, ' ') + 1));
	if (!tmp || !exec_args)
	{
		perror("tmp or exec_args memory allocation in ft_exec_args failed");
		exit(EXIT_FAILURE);
	}
	while(path[i])
		tmp[y++] = path[i++];
	tmp[y] = '\0';
	exec_args[j++] = tmp;
	i = y = 0;
	while (args[i])
	{
		while(args[i] == ' ' || args[i] == '\t')
			i++;
		if (args[i])
			tmp =  malloc (sizeof(char) * (ft_strlen_till_char(args, i, ' ') + 1));
		if (!tmp)
		{
			perror("tmp memory allocation in ft_exec_args failed");
			exit(EXIT_FAILURE);
		}
		while(args[i] != ' ' && args[i] != '\t')
			tmp[y++] = args[i++];
		tmp[y] = '\0';
		exec_args[j++] = tmp;
		y = 0;
	}
	return (exec_args);
}



// char	*ft_find_var(char *s)
// {
// 	int		i;
// 	int		j;
// 	char	*buf;
//
// 	i = 0;
// 	j = 0;
// 	while (s[i] == ' ' || s[i] == '	')
// 		i++;
// 	buf = malloc(sizeof (char) * ft_wlen(s, i));
// 	while(s[i] != ' ' || (s[i] != '	' && s[i]))
// 		buf[j++] = s[i++];
// 	if (strrchr(s, '='))
// 	{
// 		s = strchr(s, '=');
// 	}
// }
