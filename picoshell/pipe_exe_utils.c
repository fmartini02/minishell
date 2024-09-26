/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:22:27 by fmartini          #+#    #+#             */
/*   Updated: 2024/09/26 18:11:46 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_utils(t_tok *tok,char *path, char **args)//i at the beginning is 0
{
	if (tok->builtin_flag == 1 && tok->pipe_flag == 0)
	{
		tok->builtin_flag = 0;
		exit(EXIT_SUCCESS);
	}
	while (1)
	{
		if (ft_matlen((void**)tok->cmds) == 1)//if there is only one command
		{
			close(tok->pipes[tok->i][READ_END]);
			close(tok->pipes[tok->i][WRITE_END]);
			if (ft_builtins_cmds(tok, args) == 1)//if the command is a builtin
				exit(EXIT_SUCCESS);
			execve(path, args, ft_lst_2_mtx(tok->env));//getting args and executing
			ft_perror(tok, "execve failed", 1);
		}
		else if (tok->i == 0 && ft_matlen((void**)tok->cmds) > 1)
			ft_first_child(tok, path, args);
		else if (tok->i < (ft_matlen((void**)tok->cmds) - 1))
			ft_succ_childs(tok, path, args);
		else
			ft_last_child(tok, path, args);
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
		if(j != past && j != present)//if the pipe is not the one we are using
		{
			close(tok->pipes[j][READ_END]);//close the read end
			close(tok->pipes[j][WRITE_END]);//close the write end
		}
		j++;
	}
}

void	ft_first_child(t_tok *tok, char *path, char **args)
{
	char	**env;

	env = ft_lst_2_mtx(tok->env);
	ft_close_pipe(tok, tok->i, tok->i);//closing unused pipes in this process
	if (dup2(tok->pipes[tok->i][WRITE_END], STDOUT_FILENO) == -1)//redirecting the output of the command to the write end of the pipe
		ft_perror(tok, "dup2 failed", 1);
	close(tok->pipes[tok->i][READ_END]);
	close(tok->pipes[tok->i][WRITE_END]);
	if (tok->builtin_flag == 1)//if the command is a builtin
		ft_redirect_builtin_output(tok, args);
	execve(path, args, env);
	if (errno != 0)
	{
		ft_perror(tok, "execve failed", 1);
		exit(EXIT_FAILURE);
	}
}

void	ft_succ_childs(t_tok *tok, char *path, char **args)
{
	char	**env;

	env = ft_lst_2_mtx(tok->env);
	ft_close_pipe(tok, (tok->i-1), tok->i);
	if (dup2(tok->pipes[tok->i-1][READ_END], STDIN_FILENO) == -1
		|| dup2(tok->pipes[tok->i][WRITE_END], STDOUT_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(tok->pipes[tok->i-1][READ_END]);
	close(tok->pipes[tok->i-1][WRITE_END]);
	close(tok->pipes[tok->i][WRITE_END]);
	close(tok->pipes[tok->i][READ_END]);
	if (tok->builtin_flag == 1)
		ft_redirect_builtin_output(tok, args);
	execve(path, args , env);
	if (errno != 0)
	{
		ft_perror(tok, "execve failed", 1);
		exit(EXIT_FAILURE);
	}
}

void	ft_last_child(t_tok *tok, char *path, char **args)
{
	char	**env;

	env = ft_lst_2_mtx(tok->env);
	tok->last_child_flag = 1;
	ft_close_pipe(tok, (tok->i - 1), (tok->i - 1));
	if (dup2(tok->pipes[tok->i - 1][READ_END], STDIN_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(tok->pipes[tok->i - 1][READ_END]);
	close(tok->pipes[tok->i - 1][WRITE_END]);
	if (tok->builtin_flag == 1)
		ft_redirect_builtin_output(tok, args);
	execve(path, args, env);
	if (errno != 0)
	{
		ft_perror(tok, "execve failed", 1);
		exit(EXIT_FAILURE);
	}
}

