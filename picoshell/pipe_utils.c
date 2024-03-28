/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:30:54 by fmartini          #+#    #+#             */
/*   Updated: 2024/03/28 18:22:22 by fmartini         ###   ########.fr       */
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
		while(tok->str_line[i] && (tok->str_line[i] == ' ' || tok->str_line[i] == '\t'))
			i++;
		while(tok->str_line[i] && (tok->str_line[i] != ' ' && tok->str_line[i] != '\t'))
			i++;
		while(tok->str_line[i] && (tok->str_line[i] != '|'))
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
