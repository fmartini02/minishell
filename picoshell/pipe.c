/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:03:14 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/12 19:47:54 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_cmd_name(const char *s, int *i)
{
	int		tmp;
	char	*name;

	tmp = 0;
	*i = ft_skip_spaces((char*)s, *i);// skipping spaces
	name = malloc (sizeof (char) * ft_word_len(s, *i) + 1);// memory allocation for cmd name
	if (!name)
		ft_perror(NULL, "name memory allocation failed", 1);
	if (s[*i] == '|')
	{
		(*i)++;
		*i = ft_skip_spaces((char*)s, *i);
	}
	while(s[*i] != '\0' && s[*i] != ' ' && s[*i] != '\t')// cycle to get cmd name
		name[tmp++] = s[(*i)++];
	name[tmp] = '\0';// putting end of string
	return (name);
}

char	**ft_get_cmds_names_from_line(t_tok *tok)
{
	int		i;
	int		i_mat;
	char	**cmds_name;

	i_mat = 0;
	i = 0;
	cmds_name = malloc (sizeof (char *) * (ft_count_cmds(tok) + 1));// memory allocation for cmds names
	if (!cmds_name)//memory allocation check
		ft_perror(tok, "cmds_name memory allocation failed", 1);
	while (tok->str_line[i] != '\0')
	{
		cmds_name[i_mat++] = ft_extract_cmd_name(tok->str_line, &i);
		while (tok->str_line[i] != '|' && tok->str_line[i] != '\0')// skipping till the '|' char
			i++;
	}
	cmds_name[i_mat] = '\0';// putting end of matrix
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
	cmds_args = malloc (sizeof (char *) *ft_args_strlen(tok) + 1);// allocating memory for as many strings of arguments present
	while (tok->str_line[i])
	{
		i = ft_skip_spaces(tok->str_line, i);//skipping spaces
		args = malloc (sizeof (char) * ft_strlen_till_char(tok->str_line, i, ' '));//allocating memory for the string of arguments
		while (tok->str_line[i] && tok->str_line[i] != '|' && tok->str_line[i] != ' ')//copying till the char '|'
			args[j++] = tok->str_line[i++];
		args[j] = '\0';
		cmds_args[i_mat] = args;
		i_mat++;
		j = 0;
		if (tok->str_line[i] != '\0' && tok->str_line[i] == '|')
			break;
	}
	cmds_args[i_mat] = '\0';
	return (cmds_args);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");//putting '/' at the end of the path /dir/subdir + /
		command = ft_strjoin(tmp, cmd);//putting cmd at the end of the path /dir/subdir/ + cmd
		free(tmp);
		if (access(command, X_OK) == 0)//checking if the path is correct
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	ft_pipe(t_tok *tok)
{
	int			pip[2];
	pid_t		pid;
	int			i;
	char		*path;

	i = 0;
	pipe(pip);
	tok->cmds = ft_get_cmds_names_from_line(tok);
	tok->cmds_args = ft_get_cmds_args(tok);
	tok->cmds_args[0] = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);
	while (i < (ft_matlen((void **)tok->cmds) - 1))//i is incrementing inside ft_pipe_utils
	{
		path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);
		pid = fork();//creating a child process
		if (pid < 0)//checking if the fork was successful
			ft_perror(tok, "fork failed", 1);
		else if (pid == 0)//if it's a child process
			ft_pipe_utils(tok, pip, i, path, tok->cmds_args, tok->env);
		wait(NULL);//waiting for the child process to finish
		i++;
		free(path);
	}
}
