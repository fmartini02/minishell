/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:03:14 by fmartini          #+#    #+#             */
/*   Updated: 2024/04/04 17:56:02 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_cmd_name(const char *s, int *i)
{
	int		tmp;
	char	*name;

	tmp = 0;
	while(s[*i] !='\0' &&//if str_line still exist
			(s[*i] == ' ' || s [*i] == '\t'))// cycle to skip spaces
		i++;
	name = malloc (sizeof (char) * ft_word_len(s, *i) + 1);// memory allocation for cmd name
	if (!name)
	{
		perror("name memory allocation failed");
		exit(EXIT_FAILURE);
	}
	while(s[*i] != '\0' &&//check if line still exist
		s[*i] != ' ' && s[*i] != '\t')// cycle to get cmd name
		name[tmp++] = s[(*i)++];
	name[tmp] = '\0';// putting end of string
	//printf("%s\n", name);
	return (name);
}

char	**ft_get_cmds_names_from_token(t_tok *tok)
{
	int		i;
	int		i_mat;
	char	**cmds_name;

	i_mat = 0;
	i = 0;
	cmds_name = malloc (sizeof (char *) * (ft_count_cmds(tok) + 1));// memory allocation for cmds names
	if (!cmds_name)//memory allocation check
	{
		perror("cmds_name allocation failed");
		exit(EXIT_FAILURE);
	}
	while (tok->str_line[i] != '\0')
	{
		cmds_name[i_mat++] = ft_extract_cmd_name(tok->str_line, &i);
		while (tok->str_line[i] != '|' && tok->str_line[i] != '\0')// skipping till the '|' char
			i++;
	}
	cmds_name[i_mat] = '\0';
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
		args[j] = '\0';
		cmds_args[i_mat] = args;
		i_mat++;
		j = 0;
		if (tok->str_line[i] != '\0' && tok->str_line[i] == '|')//checking if the string is finished, if it isn't skip '|'
			i++;
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
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	ft_pipe(t_tok *tok, char **env)
{
	int		pip[2];
	char	*path;
	pid_t	pid;
	int		i;
	int		n_cmds;

	tok->cmds = ft_get_cmds_names_from_token(tok);
	tok->cmds_args = ft_get_cmds_args(tok);
	path = get_cmd_path(ft_split(getenv("PATH"), ':'), tok->cmds[i]);//get path var value, split for each path, testing paths, return working path
	i = 0;
	n_cmds = ft_mat_len(tok->cmds);
	pipe(pip);
	pid = fork();
	if(pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		ft_first_child(tok, pip, i, env);
	i++;
	while(i < n_cmds - 1)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			ft_succ_childs(tok, pip, i, env);
		i++;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		ft_last_child(tok, pip, i, env);
}
