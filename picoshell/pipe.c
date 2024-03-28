/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:03:14 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/28 18:45:06 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_cmds_names(t_tok *tok)
{
	int		i;
	int		tmp;
	int		i_mat;
	char	**cmds_name;
	char	*name;

	i_mat = 0;
	i = 0;
	tmp = 0;
	cmds_name = malloc (sizeof (char *) * ft_count_cmds(tok));// memory allocation for cmds names
	while (tok->str_line[i])
	{
		while(tok->str_line[i] == ' ' || tok->str_line [i] == '\t')// cycle to skip spaces
			i++;
		name = malloc (sizeof (char) * ft_word_len(tok->str_line, i) + 1);// memory allocation for cmd name
		while(tok->str_line[i] != ' ' && tok->str_line[i] != '\t')// cycle to get cmd name
			name[tmp++] = tok->str_line[i++];
		name[tmp] ='\0';// putting end of string
		cmds_name[i_mat] = name;
		i_mat++;
		tmp = 0;
		while (tok->str_line[i] != '|')// skipping till the '|' char
			i++;
	}
	return (cmds_name);
}

char	**ft_get_cmds_args(t_tok *tok)
{
	int		i;
	int		j;
	int		i_mat;
	char	**cmds_args;
	char	*args;

	i = 0;
	j = 0;
	i_mat = 0;
	cmds_args = malloc (sizeof (char *) *ft_count_args_str(tok));// allocating memory for as many strings of arguments present
	while (tok->str_line[i])
	{
		i = ft_skip(tok, i);//skipping spaces and the first word
		args = malloc (sizeof (char) * ft_strlen_till_char(tok->str_line, i, '|'));//allocating memory for the string of arguments
		while (tok->str_line[i] && tok->str_line[i] != '|')//copying till the char '|'
			args[j++] = tok->str_line[i++];
		cmds_args[i_mat] = args;
		i_mat++;
		j = 0;
		if (tok->str_line[i] == '|')//checking if the string is finished, if it isn't skip '|'
			i++;
	}
	return (cmds_args);
}

void	ft_pipe(t_tok *tok)
{
	int		pipe_fd[2];
	pid_t	pid;

	tok->cmds = ft_get_cmds_names(tok);
	tok->cmds_args = ft_get_cmds_args(tok);
	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);//closing read_end pipe
		dup2(pipe_fd[1], 1);//duplicating in the stdin the write_end pipe
		close(pipe_fd[1]);//closing write_end of pipe(fd 4 not 1)
	}
}
