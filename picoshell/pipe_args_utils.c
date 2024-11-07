/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:24:35 by fmartini          #+#    #+#             */
/*   Updated: 2024/11/07 18:44:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_args_counting_utils2(char *s, char c, int i)
{
	char	t;

	t = c;
	i++;// skip first " or '
	while (s[i] && s[i] != t)
		i++;// skip chars till last "
	i++;
	return (i);
}

int	ft_arg_count_norm_case(char *s, int *n_args, int i)
{
	while (s[i] && !ft_is_space(s[i])
			&& s[i] != '|'
			&& s[i] != '"'
			&& s[i] != '\'')
		i++;
	if (s[i] == '\n')
		i++;
	if (s[i] != '|' && !ft_is_space(s[i - 1]))
		(*n_args)++;//if string ended with a word
	else if (ft_is_space(s[i - 1]))
		(*n_args)++;
	return (i);
}

int	ft_args_counting_utils(char *s, int i, int *n_args)
{
	while (s[i] && !ft_is_space(s[i]) && s[i] != '|')//skip args
	{
		if (s[i] == '"')
		{
			i = ft_args_counting_utils2(s, '"', i);
			(*n_args)++;
		}
		if (s[i] == '\'')
		{
			i = ft_args_counting_utils2(s, '\'', i);
			(*n_args)++;
		}
		if (s[i] && !ft_is_space(s[i]))
			i = ft_arg_count_norm_case(s, n_args, i);
	}
	return (i);
}

int	ft_args_counting(t_tok *tok, int i)
{
	int	n_args_str;
	char	*line;

	n_args_str = 0;
	if (ft_count_cmds(tok) == 0)
		return(n_args_str);//if there is no cmd OR there is a problem with the syntax
	line = tok->str_line;
	while (line[i] && (line[i] != '|'))// cycle to count args
	{
		i = ft_skip_spaces(line, i);
		i = ft_args_counting_utils(line, i, &n_args_str);
	}
	if (ft_only_spaces(line))
		n_args_str = 1;
	return (n_args_str);
}
