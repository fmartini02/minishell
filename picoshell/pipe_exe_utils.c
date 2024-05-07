/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:22:27 by fmartini          #+#    #+#             */
/*   Updated: 2024/05/03 16:28:02 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_utils(t_tok *tok, int i, char *path, char **args, char **env)
{
	while (1)
	{
		if (ft_matlen((void**)tok->cmds) == 1) //if there is only one command
		{
			close(tok->pipes[i][READ_END]);
			close(tok->pipes[i][WRITE_END]);
			execve(path, args, env);//getting args and executing
			ft_perror(tok, "execve failed", 1);
		}
		else if (i == 0 && ft_matlen((void**)tok->cmds) > 1)
			ft_first_child(tok, path, args, env, i);
		else if (i < (ft_matlen((void**)tok->cmds) - 1))
			ft_succ_childs(tok, path, args, env, i);
		else
			ft_last_child(tok, path, args, env, i);
	}
}

void	ft_close_pipe(t_tok *tok, int past, int present)
{
	int	mat_len;
	int	j;

	mat_len = ft_matlen((void**)tok->pipes);
	j = 0;
	while (j < mat_len)
	{
		if(j != past && j != present)
		{
			close(tok->pipes[j][READ_END]);
			close(tok->pipes[j][WRITE_END]);
		}
		j++;
	}
}

void	ft_first_child(t_tok *tok, char *path, char **args, char **env, int i)
{
	//printf("first child\n");
	ft_close_pipe(tok, i, i);
	if (dup2(tok->pipes[i][WRITE_END], STDOUT_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(tok->pipes[i][READ_END]);
	close(tok->pipes[i][WRITE_END]);
	execve(path, args, env);
	if (errno != 0)
	{
		ft_perror(tok, "execve failed", 1);
		exit(EXIT_FAILURE);
	}
}

void	ft_succ_childs(t_tok *tok, char *path, char **args, char **env, int i)
{
	ft_close_pipe(tok, (i-1), i);
	if (dup2(tok->pipes[i-1][READ_END], STDIN_FILENO) == -1 || dup2(tok->pipes[i][WRITE_END], STDOUT_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(tok->pipes[i-1][READ_END]);
	close(tok->pipes[i-1][WRITE_END]);
	close(tok->pipes[i][WRITE_END]);
	close(tok->pipes[i][READ_END]);
	execve(path, args , env);
	if (errno != 0)
	{
		ft_perror(tok, "execve failed", 1);
		exit(EXIT_FAILURE);
	}
}

void	ft_last_child(t_tok *tok, char *path, char **args, char **env, int i)
{
	//printf("last child\n");
	ft_close_pipe(tok, (i - 1), (i - 1));
	if (dup2(tok->pipes[i-1][READ_END], STDIN_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(tok->pipes[i-1][READ_END]);
	close(tok->pipes[i-1][WRITE_END]);
	execve(path, args, env);
	if (errno != 0)
	{
		ft_perror(tok, "execve failed", 1);
		exit(EXIT_FAILURE);
	}
}

