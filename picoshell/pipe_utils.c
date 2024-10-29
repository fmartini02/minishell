/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:36:52 by francema          #+#    #+#             */
/*   Updated: 2024/10/14 17:14:41 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (((line[i] >='\t' && line[i] <= '\r')) || line[i] == ' '))
		i++;
	if (line[i] == '\0')//if the line is only spaces
		return (1);
	else
		return (0);
}

int	ft_skip_quoted_words(char *s, int i)
{
	if (s[i] == '"')
	{
		i++;//skip first "
		while(s[i] && s[i] != '"')
			i++;
		i++;//skip last "
	}
	else if (s[i] == '\'')
	{
		i++;//skip first '
		while(s[i] && s[i] != '\'')
			i++;
		i++;//skip last '
	}
	return (i);
}

int	ft_count_cmds_utils(char *s, int *i, t_tok *tok)
{
	int	j;

	j = *i;
	if (s[j] == '"' || s[j] == '\'')
		j = ft_skip_quoted_words(s, j);
	while (s[j] && s[j] != '|')
		j++;//to skip args
	if (s[j] && s[j] == '|')
	{
		j++;//skip |
		tok->pipe_flag = 1;
		j = ft_skip_spaces(s, j);
		if (s[j] == '|' || !s[j])
			return (0);
	}
	*i = j;
	return (1);
}

int	ft_count_cmds(t_tok *tok)
{
	int		i;
	int		n_cmds;
	char	*s;

	s = tok->str_line;
	n_cmds = 0;
	if (ft_only_spaces(s))
		return (n_cmds);
	i = ft_skip_spaces(s, 0);
	if (s[i] == '|')
	{
		tok->pipe_flag = 1;
		return (n_cmds);
	}
	while (s[i])
	{
		if (s[i] != '|' && s[i] && s[i] >= '!' && s[i] <= '~')
		{
			n_cmds += 1;
			if (!ft_count_cmds_utils(s, &i, tok))
				return (0);
		}
		i = ft_skip_spaces(s, i);
	}
	return (n_cmds);
}
