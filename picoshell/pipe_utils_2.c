/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:09:08 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/09 17:48:05 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_first_child(t_tok *tok, int *pipe, int i, char **env)
{
	char			*path;
	char* const*	exec;

	path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);//get path var value, split for each path, testing paths, return working path
	printf("path: %s\n", path);
	if (dup2(pipe[WRITE_END], STDOUT_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(pipe[0]);
	close(pipe[1]);
	exec = ft_exec_args(tok->cmds_args[i], tok);
	printf("exec: %s\n", exec[0]);
	execve(path, exec, env);
	ft_perror(tok, "execve failed", 1);
	exit(EXIT_FAILURE);
}

void	ft_succ_childs(t_tok *tok, int *pipe, int i, char **env)
{
	char			*path;
	char* const*	exec;

	path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);//get path var value, split for each path, testing paths, return working path
	if (dup2(pipe[READ_END], STDIN_FILENO) == -1 || dup2(pipe[WRITE_END], STDOUT_FILENO) == -1)
		ft_perror(tok, "dup2 failed", 1);
	close(pipe[0]);
	close(pipe[1]);
	exec = ft_exec_args(tok->cmds_args[i], tok);
	execve(path, exec , env);
	ft_perror(tok, "execve failed", 1);
	exit(EXIT_FAILURE);
}

void	ft_last_child(t_tok *tok, int *pipe, int i, char ** env)
{
	char			*path;
	char* const*	exec;

	path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);//get path var value, split for each path, testing paths, return working path
	if (dup2(pipe[READ_END], STDIN_FILENO) == -1)
	ft_perror(tok, "dup2 failed", 1);
	close(pipe[0]);
	close(pipe[1]);
	exec = ft_exec_args(tok->cmds_args[i], tok);
	execve(path, exec, env);
	ft_perror(tok, "execve failed", 1);
	exit(EXIT_FAILURE);
}
