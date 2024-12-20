/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:47:06 by fmartini          #+#    #+#             */
/*   Updated: 2024/11/05 18:37:54 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_words(const char *s)
{
	int word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s)
			word_count++;
		while (*s && *s != ' ' && *s != '\t')
			s++;
	}
	return (word_count);
}

void	ft_builtins_presence(t_tok *tok, int i)
{
	if (!tok->cmds_args)
	{
		tok->builtin_presence = 0;
		return ;
	}
	if (!ft_strcmp(tok->cmds_args[i][0], "cd") || !ft_strcmp(tok->cmds_args[i][0], "echo")
		|| !ft_strcmp(tok->cmds_args[i][0], "pwd") || !ft_strcmp(tok->cmds_args[i][0], "export")
		|| !ft_strcmp(tok->cmds_args[i][0], "env") || !ft_strcmp(tok->cmds_args[i][0], "unset")
		|| !ft_strcmp(tok->cmds_args[i][0], "exit") || !ft_strcmp(tok->cmds_args[i][0], "clear"))
			tok->builtin_presence = 1;
	else
		tok->builtin_presence = 0;
}

int	ft_vars_len(const char *s)
{
	int		i;
	int		len;
	int		temp_i;
	char	*temp_str;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			temp_i = i;
			temp_str = ft_db_q_case(s, &temp_i);
			if (temp_str)
			{
				len += ft_strlen(temp_str);
				free(temp_str);
			}
			i = temp_i;
		}
		else
			i++;
	}
	return (len);
}

void	handle_nwline_in_norm_case(char *str, int *i, int *j)
{
	str[(*j)++] = ' ';
	(*i)++;
}
