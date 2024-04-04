/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:30:54 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/04 18:07:40 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_cmds(t_tok *tok)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	while (tok->str_line[i])
	{
		if (tok->str_line[i] == '|')// cycle to count how many cmds there are
			tmp +=1;
		i++;
	}
	return (tmp);
}

int	ft_count_args_str(t_tok *tok)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	while (tok->str_line[i])
	{
		while(tok->str_line[i] && (tok->str_line[i] == ' ' || tok->str_line[i] == '\t')) // skipping spaces
			i++;
		while(tok->str_line[i] && (tok->str_line[i] != ' ' && tok->str_line[i] != '\t'))// skipping first word
			i++;
		while(tok->str_line[i] && (tok->str_line[i] != '|'))// skipping till '|' char
			i++;
		if (tok->str_line[i] == '|')
		{
			tmp += 1;
			i++;
		}
	}
	return (tmp);
}

int	ft_skip(t_tok *tok, int i)
{
	while(tok->str_line[i] == ' ' || tok->str_line [i] == '\t')// cycle to skip spaces
		i++;
	while(tok->str_line[i] && (tok->str_line[i] != ' ' && tok->str_line[i] != '\t'))//cycle to skip first word
		i++;
	return(i);
}

void	ft_first_child(t_tok *tok, int *pipe, int i, char **env)
{
	char	*path;

	path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);
	if (dup2(pipe[WRITE_END], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
	close(pipe[0]);
	close(pipe[1]);
	execve(path, tok->cmds_args[i], env);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

void	ft_succ_childs(t_tok *tok, int *pipe, int i, char **env)
{
	char	*path;

	path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);
	if (dup2(pipe[READ_END], STDIN_FILENO) == -1 || dup2(pipe[WRITE_END], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
	close(pipe[0]);
	close(pipe[1]);
	execve(path, tok->cmds_args[i], env);
	perror("execve failed");
	exit(EXIT_FAILURE);
}
void	ft_last_child(t_tok *tok, int *pipe, int i, char ** env)
{
	char	*path;

	path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);
	if (dup2(pipe[READ_END], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
	close(pipe[0]);
	close(pipe[1]);
	execve(path, tok->cmds_args[i], env);
	perror("execve failed");
	exit(EXIT_FAILURE);
}
