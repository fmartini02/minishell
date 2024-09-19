/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:24:35 by fmartini          #+#    #+#             */
/*   Updated: 2024/09/19 16:05:11 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ft_args_counting_utils(char *s, char c, int i)
{
	i++;//skip first "
	while (s[i] != c && s[i] != '\0')
		i++;// skip chars till last "
	i++;// skip last "
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
			n_cmds +=1;
		i++;
	}
	return (n_cmds);
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
		while (line[i] && line[i] != ' ' && line[i] != '\t')//skip args
		{
			if (line[i] == '"')
				i = ft_args_counting_utils(line, '"', i);
			if (line[i] == '\'')
				i = ft_args_counting_utils(line, '\'', i);
			i++;
		}
		if (line[i])
			n_args_str++;
		i = ft_skip_spaces(line, i);
	}
	if (ft_only_spaces(line))
		n_args_str = 1;
	return (n_args_str);
}
