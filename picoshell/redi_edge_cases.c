/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_edge_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:18 by francema          #+#    #+#             */
/*   Updated: 2024/11/06 17:35:25 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redi_check_utils(char *s, int i, char c)
{
	if (s[i] == c)
	{
		printf("minishell: syntax error near unexpected token `%c'\n", c);
		return (1);
	}
	return (0);
}

int	check_dir(char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '|')
		i++;
	if (s[i - 1] == '/')
		return (1);
	else
		return (0);
}

int	redi_check(char *s, int i)
{
	if (s[i] && s[i] == ' ')
		i = ft_skip_spaces(s, i);
	if (redi_check_utils(s, i, '\0')
		|| redi_check_utils(s, i, '|')
		|| redi_check_utils(s, i, '>')
		|| redi_check_utils(s, i, '&')
		|| redi_check_utils(s, i, '<'))
		return (1);
	else if (check_dir(s,i))
	{
		printf("minishell: %s: Is a directory", ft_get_word_from_indx(s, i));
		return (1);
	}
	else
		return (0);
}

int	redi_check_inputs(t_redi *redi, int i)
{
	char	*s;

	s = redi->s;
	if (!s[i + 1])
	{
		redi->ret_code = SYNTX;
		redi_error_msgs(redi);
		return (1);
	}
	if (s[i + 1] && s[i + 1] == ' ')
	{
		if (redi_check(s, i + 1))
			return (1);
	}
	else if (s[i + 1] && s[i + 1] == '&')
	{
		if (redi_check(s, i + 2))//to skip also &
			return (1);
	}
	return (0);
}
