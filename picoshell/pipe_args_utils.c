/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:24:35 by fmartini          #+#    #+#             */
/*   Updated: 2024/10/15 16:04:52 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_args_counting_utils2(char *s, char c, int i)
{
	char	t;

	t = c;
	i++;// skip first " or '
	while (s[i] != t && s[i] != '\0')
		i++;// skip chars till last "
	i++;
	return (i);
}

int	ft_arg_count_norm_case(char *s, int *n_args, int i)
{
	while (s[i] && s[i] != '\'' && s[i] != '"' && s[i] != '|' && *n_args != 0)
		i++;//skip next args
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '|')
		i++;//skip first arg(cmd name)
	if (s[i] != '|')
		(*n_args)++;
	return (i);
}

int	ft_args_counting_utils(char *s, int i, int *n_args)
{
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '|')//skip args
	{
		if (s[i] == '"')
		{
			i = ft_args_counting_utils2(s, '"', i);
			if (s[i] == '\0')
				(*n_args)++;
		}
		if (s[i] == '\'')
		{
			i = ft_args_counting_utils2(s, '\'', i);
			if (s[i] == '\0')
				(*n_args)++;
		}
		if (s[i] && s[i] != ' ' && s[i] != '\t')
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
		if (line[i] && line[i] != '|')
			n_args_str++;
	}
	if (ft_only_spaces(line))
		n_args_str = 1;
	return (n_args_str);
}
