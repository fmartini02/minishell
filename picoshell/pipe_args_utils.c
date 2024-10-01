/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:24:35 by fmartini          #+#    #+#             */
/*   Updated: 2024/10/01 18:09:09 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_args_counting_utils(char *s, char c, int i)
{
	char	t;

	t = c;
	i++;
	while (s[i] != t && s[i] != '\0')
		i++;// skip chars till last "
	i++;
	return (i);
}

int	ft_count_cmds(t_tok *tok)
{
	int	i;
	int	n_cmds;

	i = 0;
	n_cmds = 1;
	while (tok->str_line[i])
	{
		if (tok->str_line[i] == '|')// cycle to count how many cmds there are
		{
			n_cmds +=1;
			tok->pipe_flag = 1;
		}
		i++;
	}
	return (n_cmds);
}

int	ft_args_counting_utils2(char *s, int i, int *n_args)
{
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '|')//skip args
	{
		if (s[i] == '"')
		{
			i = ft_args_counting_utils(s, '"', i);
			if (s[i] == '\0')
				(*n_args)++;
		}
		if (s[i] == '\'')
		{
			i = ft_args_counting_utils(s, '\'', i);
			if (s[i] == '\0')
				(*n_args)++;
		}
		if (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	return (i);
}

int	ft_args_counting(t_tok *tok, int i)
{
	int	n_args_str;
	char	*line;

	n_args_str = 0;
	line = tok->str_line;
	while (line[i] && (line[i] != '|'))// cycle to count args
	{
		i = ft_skip_spaces(line, i);
		i = ft_args_counting_utils2(line, i, &n_args_str);//n_args_str if the str end increment
		if (line[i] && line[i] != '|')
			n_args_str++;
	}
	if (ft_only_spaces(line))
		n_args_str = 1;
	return (n_args_str);
}
